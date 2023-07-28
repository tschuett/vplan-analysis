#pragma once

class VPBlock;

class VPlan {
  /// Hold the single entry to the Hierarchical CFG of the VPlan, i.e. the
  /// preheader of the vector loop.
  VPBlock *Entry;

public:
  VPBlock *getEntry() const { return Entry; }
};

//template <> struct llvm::GraphTraits<VPlan *> {
//  using NodeRef = VPBlock *;
//  using nodes_iterator =
//      df_iterator<VPBlock *, df_iterator_default_set<VPBlock *>>;
//
//  static NodeRef getEntryNode(VPlan *VP) { return VP->getEntry(); }
//
//  static nodes_iterator nodes_begin(NodeRef N) {
//    return df_begin(getEntryNode(N));
//  }
//
//  static nodes_iterator nodes_end(NodeRef *N) {
//    return df_end(getEntryNode(N));
//  }
//};
