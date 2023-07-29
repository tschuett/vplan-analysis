#pragma once

#include "Plan.h"

#include <llvm/ADT/SmallVector.h>
#include <llvm/Support/raw_ostream.h>
#include <string>

class VPRegionBlock;

class VPBlockBase {
  VPRegionBlock *Parent;

  /// List of predecessor blocks.
  llvm::SmallVector<VPBlockBase *, 1> Predecessors;

  /// List of successor blocks.
  llvm::SmallVector<VPBlockBase *, 1> Successors;

  /// VPlan containing the block. Can only be set on the entry block of the
  /// plan.
  VPlan *Plan = nullptr;

  std::string Name;

  using succ_iterator = llvm::SmallVector<VPBlockBase *, 1>::iterator;

public:
  enum class BlockKind { VPBasicBlockSC, VPRegionBlockSC };

  /// \return an ID for the concrete type of this object.
  /// This is used to implement the classof checks. This should not be used
  /// for any other purpose, as the values may change as LLVM evolves.
  BlockKind getVPBlockID() const { return SubclassID; }

  VPlan *getPlan() const { return Plan; }
  VPRegionBlock *getParent() const { return Parent; }

  const std::string &getName() const { return Name; }

  succ_iterator succ_begin() const { return succ_iterator(Successors.begin()); }
  succ_iterator succ_end() const { return succ_iterator(Successors.end()); }

  void printAsOperand(llvm::raw_ostream &OS, bool PrintType) const {
    OS << getName();
  }

  size_t getNumSuccessors() const { return Successors.size(); }

  const llvm::SmallVector<VPBlockBase *, 1> &getSuccessors() const {
    return Successors;
  }
  llvm::SmallVector<VPBlockBase *, 1> &getSuccessors() { return Successors; }

protected:
  VPBlockBase(const BlockKind SC, const std::string &N)
      : Name(N), SubclassID(SC) {}

private:
  const BlockKind SubclassID; ///< Subclass identifier (for isa/dyn_cast).
};
