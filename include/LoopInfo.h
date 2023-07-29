#pragma once

#include "BlockBase.h"
#include "DomTree.h"

#include <llvm/Support/GenericLoopInfo.h>

class VPLoop;
class VPLoopInfo;

extern template class llvm::LoopBase<VPBlockBase, VPLoop>;

class VPLoop : public llvm::LoopBase<VPBlockBase, VPLoop> {};

extern template class llvm::LoopInfoBase<VPBlockBase, VPLoop>;

class VPLoopInfo : public llvm::LoopInfoBase<VPBlockBase, VPLoop> {
public:
  explicit VPLoopInfo(
      const llvm::DominatorTreeBase<VPBlockBase, false> &DomTree);
};
