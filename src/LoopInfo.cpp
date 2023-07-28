#include "LoopInfo.h"

#include "DomTree.h"
#include "Traits.h"

using namespace llvm;

template
void LoopInfoBase<VPBlockBase, VPLoop>::analyze(
    const llvm::DominatorTreeBase<VPBlockBase, false> &);

int bar() {
  // VPlan plan;  FIXME: implicit
  VPDomTree domTree;

  llvm::DomTreeBuilder::Calculate(domTree);

  VPLoopInfo loopInfo;

  loopInfo.analyze(domTree);

  return 1;
}
