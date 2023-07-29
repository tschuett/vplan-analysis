#pragma once

#include "RegionBlock.h"

#include <llvm/ADT/DepthFirstIterator.h>
#include <llvm/ADT/GraphTraits.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/iterator.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/ErrorHandling.h>

template <typename BlockPtrTy>
class VPAllSuccessorsIterator
    : public llvm::iterator_facade_base<VPAllSuccessorsIterator<BlockPtrTy>,
                                        std::bidirectional_iterator_tag,
                                        VPBlockBase> {
  BlockPtrTy Block;
  /// Index of the current successor. For VPBasicBlock nodes, this simply is the
  /// index for the successor array. For VPRegionBlock, SuccessorIdx == 0 is
  /// used for the region's entry block, and SuccessorIdx - 1 are the indices
  /// for the successor array.
  size_t SuccessorIdx;

  static BlockPtrTy getBlockWithSuccs(BlockPtrTy Current) {
    while (Current && Current->getNumSuccessors() == 0)
      Current = Current->getParent();
    return Current;
  }

  /// Templated helper to dereference successor \p SuccIdx of \p Block. Used by
  /// both the const and non-const operator* implementations.
  template <typename T1> static T1 deref(T1 Block, unsigned SuccIdx) {
    if (auto *R = llvm::dyn_cast<VPRegionBlock>(Block)) {
      assert(SuccIdx == 0);
      return R->getEntry();
    }

    // For exit blocks, use the next parent region with successors.
    return getBlockWithSuccs(Block)->getSuccessors()[SuccIdx];
  }

public:
  /// Used by iterator_facade_base with bidirectional_iterator_tag.
  using reference = BlockPtrTy;

  VPAllSuccessorsIterator(BlockPtrTy Block, size_t Idx = 0)
      : Block(Block), SuccessorIdx(Idx) {}
  VPAllSuccessorsIterator(const VPAllSuccessorsIterator &Other)
      : Block(Other.Block), SuccessorIdx(Other.SuccessorIdx) {}

  VPAllSuccessorsIterator &operator=(const VPAllSuccessorsIterator &R) {
    Block = R.Block;
    SuccessorIdx = R.SuccessorIdx;
    return *this;
  }

  static VPAllSuccessorsIterator end(BlockPtrTy Block) {
    if (auto *R = llvm::dyn_cast<VPRegionBlock>(Block)) {
      // Traverse through the region's entry node.
      return {R, 1};
    }
    BlockPtrTy ParentWithSuccs = getBlockWithSuccs(Block);
    unsigned NumSuccessors =
        ParentWithSuccs ? ParentWithSuccs->getNumSuccessors() : 0;
    return {Block, NumSuccessors};
  }

  bool operator==(const VPAllSuccessorsIterator &R) const {
    return Block == R.Block && SuccessorIdx == R.SuccessorIdx;
  }

  const VPBlockBase *operator*() const { return deref(Block, SuccessorIdx); }

  BlockPtrTy operator*() { return deref(Block, SuccessorIdx); }

  VPAllSuccessorsIterator &operator++() {
    SuccessorIdx++;
    return *this;
  }

  VPAllSuccessorsIterator &operator--() {
    SuccessorIdx--;
    return *this;
  }

  VPAllSuccessorsIterator operator++(int X) {
    VPAllSuccessorsIterator Orig = *this;
    SuccessorIdx++;
    return Orig;
  }
};

template <> struct llvm::GraphTraits<VPBlockBase *> {
  using NodeRef = VPBlockBase *;
  using ChildIteratorType = VPAllSuccessorsIterator<VPBlockBase *>;

  static NodeRef getEntryNode(NodeRef N) { return N; }

  static inline ChildIteratorType child_begin(NodeRef N) {
    return ChildIteratorType(N);
  }

  static inline ChildIteratorType child_end(NodeRef N) {
    return ChildIteratorType::end(N);
  }
};

template <> struct llvm::GraphTraits<const VPBlockBase *> {
  using NodeRef = const VPBlockBase *;
  using ChildIteratorType = VPAllSuccessorsIterator<const VPBlockBase *>;

  static NodeRef getEntryNode(NodeRef N) { return N; }

  static inline ChildIteratorType child_begin(NodeRef N) {
    return ChildIteratorType(N);
  }

  static inline ChildIteratorType child_end(NodeRef N) {
    return ChildIteratorType::end(N);
  }
};

/// Inverse graph traits are not implemented yet.
/// TODO: Implement a version of VPBlockNonRecursiveTraversalWrapper to traverse
/// predecessors recursively through regions.
template <> struct llvm::GraphTraits<llvm::Inverse<VPBlockBase *>> {
  using NodeRef = VPBlockBase *;
  using ChildIteratorType = llvm::SmallVectorImpl<VPBlockBase *>::iterator;

  static NodeRef getEntryNode(Inverse<NodeRef> B) {
    llvm_unreachable("not implemented");
  }

  static inline ChildIteratorType child_begin(NodeRef N) {
    llvm_unreachable("not implemented");
  }

  static inline ChildIteratorType child_end(NodeRef N) {
    llvm_unreachable("not implemented");
  }
};

template <> struct llvm::GraphTraits<VPlan *> {
  using GraphRef = VPlan *;
  using NodeRef = VPBlockBase *;
  using nodes_iterator = df_iterator<NodeRef>;

  static NodeRef getEntryNode(GraphRef N) { return N->getEntry(); }

  static nodes_iterator nodes_begin(GraphRef N) {
    return nodes_iterator::begin(N->getEntry());
  }

  static nodes_iterator nodes_end(GraphRef N) {
    // df_iterator::end() returns an empty iterator so the node used doesn't
    // matter.
    return nodes_iterator::end(N->getEntry());
  }
};
