#pragma once

#include "Block.h"
#include "Plan.h"

#include <llvm/ADT/DepthFirstIterator.h>
#include <llvm/ADT/GraphTraits.h>
#include <llvm/IR/Dominators.h>
#include <llvm/Support/GenericDomTree.h>

using VPDomTreeNode = llvm::DomTreeNodeBase<VPBlockBase>;
using VPDomTree = llvm::DomTreeBase<VPBlockBase>;


template <> struct llvm::DomTreeNodeTraits<VPBlockBase> {
  using NodeType = VPBlockBase;
  using NodePtr = VPBlockBase *;
  using ParentPtr = VPlan *;

  static NodePtr getEntryNode(ParentPtr Parent) { return Parent->getEntry(); }
  static ParentPtr getParent(NodePtr B) { return B->getPlan(); }
};

//class VPDomTree : public llvm::DominatorTreeBase<VPBlockBase, false> {
//public:
//  using Base = llvm::DominatorTreeBase<VPBlockBase, false>;
//
//  VPDomTree() = default;
//  explicit VPDomTree(VPlan &p) { recalculate(p); }
//
//  // Ensure base-class overloads are visible.
//  using Base::dominates;
//};

namespace llvm::DomTreeBuilder {

extern template void Calculate<VPDomTree>(VPDomTree &DT);

//extern template void
//CalculateWithUpdates<VPDomTree>(VPDomTree &DT,
//                                llvm::ArrayRef<VPDomTree::UpdateType> U);

} // namespace llvm::DomTreeBuilder

//===-------------------------------------
// DominatorTree GraphTraits specializations so the DominatorTree can be
// iterable by generic graph iterators.

// template <class Node, class ChildIterator> struct DomTreeGraphTraitsBase {
//   using NodeRef = Node *;
//   using ChildIteratorType = ChildIterator;
//   using nodes_iterator =
//       llvm::df_iterator<Node *, llvm::df_iterator_default_set<Node *>>;
//
//   static NodeRef getEntryNode(NodeRef N) { return N; }
//   static ChildIteratorType child_begin(NodeRef N) { return N->begin(); }
//   static ChildIteratorType child_end(NodeRef N) { return N->end(); }
//
//   static nodes_iterator nodes_begin(NodeRef N) {
//     return df_begin(getEntryNode(N));
//   }
//
//   static nodes_iterator nodes_end(NodeRef N) { return
//   df_end(getEntryNode(N)); }
// };

template <>
struct llvm::GraphTraits<VPDomTreeNode *>
    : public llvm::DomTreeGraphTraitsBase<VPDomTreeNode,
                                          VPDomTreeNode::const_iterator> {};

template <>
struct llvm::GraphTraits<const VPDomTreeNode *>
    : public llvm::DomTreeGraphTraitsBase<const VPDomTreeNode,
                                          VPDomTreeNode::const_iterator> {};

// template <>
// struct llvm::GraphTraits<VPDomTree *>
//     : public llvm::GraphTraits<DomTreeNode *> {
//   static NodeRef getEntryNode(VPDomTree *DT) { return DT->getRootNode(); }
//
//   static nodes_iterator nodes_begin(VPDomTree *N) {
//     return df_begin(getEntryNode(N));
//   }
//
//   static nodes_iterator nodes_end(VPDomTree *N) {
//     return df_end(getEntryNode(N));
//   }
//}
