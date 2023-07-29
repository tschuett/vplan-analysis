#include "DomTree.h"

#include "Traits.h"

#include <llvm/Support/GenericDomTreeConstruction.h>

using namespace llvm;

template class llvm::DomTreeNodeBase<VPBlockBase>;
template class llvm::DominatorTreeBase<VPBlockBase, false>; // DomTreeBase

template void DomTreeBuilder::Calculate<VPDomTree>(VPDomTree &DT);

//template void GenericDomTree::recalculate<VPBlockBase, false>(VPDomTree &DT);

// template llvm::DomTreeBuilder::CalculateWithUpdates<VPDomTree>(
//     VPDomTree &DT, llvm::ArrayRef<llvm::cfg::Update<VPBlock *>> U);

int foo() {
  VPlan plan;
  VPDomTree domTree;

  domTree.recalculate(plan);

  VPBlock *block0 = nullptr;
  VPBlock *block1 = nullptr;

  if (domTree.dominates(block0, block1)) {
  }

  return 1;
}
