#pragma once

#include "Block.h"
#include "Function.h"

#include <llvm/Support/GenericDomTree.h>

// #include <llvm/Support/GenericDomTreeConstruction.h>
#include <llvm/ADT/DepthFirstIterator.h>
#include <llvm/ADT/GraphTraits.h>

using DomTreeNode = llvm::DomTreeNodeBase<VPBlock>;

class VPDomTree : public llvm::DominatorTreeBase<VPBlock, false> {
public:
  using Base = llvm::DominatorTreeBase<VPBlock, false>;

  VPDomTree() = default;
  // explicit VPDomTree(VPFunction &F) { recalculate(F); }

  // Ensure base-class overloads are visible.
  using Base::dominates;
};

//===-------------------------------------
// DominatorTree GraphTraits specializations so the DominatorTree can be
// iterable by generic graph iterators.

template <class Node, class ChildIterator> struct DomTreeGraphTraitsBase {
  using NodeRef = Node *;
  using ChildIteratorType = ChildIterator;
  using nodes_iterator =
      llvm::df_iterator<Node *, llvm::df_iterator_default_set<Node *>>;

  static NodeRef getEntryNode(NodeRef N) { return N; }
  static ChildIteratorType child_begin(NodeRef N) { return N->begin(); }
  static ChildIteratorType child_end(NodeRef N) { return N->end(); }

  static nodes_iterator nodes_begin(NodeRef N) {
    return df_begin(getEntryNode(N));
  }

  static nodes_iterator nodes_end(NodeRef N) { return df_end(getEntryNode(N)); }
};

template <>
struct llvm::GraphTraits<DomTreeNode *>
    : public DomTreeGraphTraitsBase<DomTreeNode, DomTreeNode::const_iterator> {
};

template <>
struct llvm::GraphTraits<const DomTreeNode *>
    : public DomTreeGraphTraitsBase<const DomTreeNode,
                                    DomTreeNode::const_iterator> {};

template <>
struct llvm::GraphTraits<VPDomTree *> : public llvm::GraphTraits<DomTreeNode *> {
  static NodeRef getEntryNode(VPDomTree *DT) { return DT->getRootNode(); }

  static nodes_iterator nodes_begin(VPDomTree *N) {
    return df_begin(getEntryNode(N));
  }

  static nodes_iterator nodes_end(VPDomTree *N) {
    return df_end(getEntryNode(N));
  }
};

