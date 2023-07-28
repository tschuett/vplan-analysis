#pragma once

#include "BlockBase.h"

#include <llvm/ADT/DepthFirstIterator.h>
#include <llvm/ADT/GraphTraits.h>
#include <llvm/ADT/SmallVector.h>

class VPRegionBlock : public VPBlockBase {
  VPBlockBase *Entry;
  // VPBlockBase *Exiting;

public:
  VPBlockBase *getEntry() const { return Entry; }

  /// Method to support type inquiry through isa, cast, and dyn_cast.
  static inline bool classof(const VPBlockBase *V) {
    return V->getVPBlockID() == VPBlockBase::BlockKind::VPRegionBlockSC;
  }
};

using succ_iterator = llvm::SmallVector<VPBlockBase *, 1>::iterator;

// template <> struct llvm::GraphTraits<VPRegionBlock *> {
//   using NodeRef = VPBlockBase *;
//   using ChildIteratorType = succ_iterator;
//
//   static NodeRef getEntryNode(VPRegionBlock *BB) { return BB; }
//   static ChildIteratorType child_begin(NodeRef N) { return N->succ_begin(); }
//   static ChildIteratorType child_end(NodeRef N) { return N->succ_end(); }
// };
