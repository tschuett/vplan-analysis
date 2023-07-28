#include "DomTree.h"
#include "Traits.h"

#include <llvm/Support/GenericDomTreeConstruction.h>

using namespace llvm;

template void DomTreeBuilder::Calculate<VPDomTree>(VPDomTree &DT);

//template llvm::DomTreeBuilder::CalculateWithUpdates<VPDomTree>(
//    VPDomTree &DT, llvm::ArrayRef<llvm::cfg::Update<VPBlock *>> U);

int foo() {
  VPDomTree domTree;
  VPBlock *block0 = nullptr;
  VPBlock *block1 = nullptr;

  if (domTree.dominates(block0, block1)) {
  }

  return 1;
}
