#pragma once

#include "Function.h"

#include <llvm/ADT/DepthFirstIterator.h>
#include <llvm/ADT/GraphTraits.h>
#include <llvm/ADT/SmallVector.h>

class VPBlock;

using succ_iterator = llvm::SmallVector<VPBlock *, 1>::iterator;

class VPBlock final {
  /// List of successor blocks.
  llvm::SmallVector<VPBlock *, 1> Successors;

public:
  VPFunction *getParent();

  succ_iterator succ_begin() const { return succ_iterator(Successors.begin()); }
  succ_iterator succ_end() const { return succ_iterator(Successors.end()); }
};

template <> struct llvm::GraphTraits<VPBlock *> {
  using NodeRef = VPBlock *;
  using ChildIteratorType = succ_iterator;

  static NodeRef getEntryNode(VPBlock *BB) { return BB; }
  static ChildIteratorType child_begin(NodeRef N) { return N->succ_begin(); }
  static ChildIteratorType child_end(NodeRef N) { return N->succ_end(); }
};

template <> struct llvm::GraphTraits<const VPBlock *> {
  using NodeRef = const VPBlock *;
  using ChildIteratorType = succ_iterator;

  static NodeRef getEntryNode(const VPBlock *BB) { return BB; }

  static ChildIteratorType child_begin(NodeRef N) { return N->succ_begin(); }
  static ChildIteratorType child_end(NodeRef N) { return N->succ_end(); }
};
