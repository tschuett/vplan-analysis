#pragma once

#include "Block.h"

#include <llvm/Support/GenericLoopInfo.h>

class VPLoop : public llvm::LoopBase<VPBlock, VPLoop> {};

class VPLoopInfo : public llvm::LoopInfoBase<VPBlock, VPLoop> {};
