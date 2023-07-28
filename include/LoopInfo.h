#pragma once

#include "BlockBase.h"
#include "DomTree.h"

#include <llvm/Support/GenericLoopInfo.h>

class VPLoop : public llvm::LoopBase<VPBlockBase, VPLoop> {};

class VPLoopInfo : public llvm::LoopInfoBase<VPBlockBase, VPLoop> {};

namespace llvm {

//extern template void LoopInfoBase<VPBlockBase, VPLoop>::analyze(
//    const llvm::DominatorTreeBase<VPBlockBase, false> &);

}
