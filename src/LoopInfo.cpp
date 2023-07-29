#include "LoopInfo.h"

#include "DomTree.h"
#include "Traits.h"

#include <llvm/Support/raw_ostream.h>

using namespace llvm;

// template<>
// void LoopInfoBase<VPBlockBase, VPLoop>::analyze(
//     const llvm::DominatorTreeBase<VPBlockBase, false> &DomTree);

// Explicitly instantiate methods in LoopInfoImpl.h for IR-level Loops.
template class llvm::LoopBase<VPBlockBase, VPLoop>;
template class llvm::LoopInfoBase<VPBlockBase, VPLoop>;

// template <>
// void LoopInfoBase<VPBlockBase, VPLoop>::analyze(
//     const llvm::DominatorTreeBase<VPBlockBase, false> &DomTree);

// template <>
// void LoopInfoBase<VPBlockBase, VPLoop>::print(raw_ostream &OS) const;

VPLoopInfo::VPLoopInfo(const llvm::DomTreeBase<VPBlockBase> &DomTree) {
  analyze(DomTree);
}

int bar() {
  // VPlan plan;  FIXME: implicit
  VPDomTree domTree;

  llvm::DomTreeBuilder::Calculate(domTree);

  VPLoopInfo loopInfo(domTree);

  // loopInfo.analyze(domTree);

  loopInfo.print(llvm::outs());

  llvm::outs() << "foo";

  return 1;
}
