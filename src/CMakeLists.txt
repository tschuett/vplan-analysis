add_library(VPlanAnalysis
           DomTree.cpp
           LoopInfo.cpp
           BlockBase.cpp
           Block.cpp
           RegionBlock.cpp
           )


target_include_directories(VPlanAnalysis PRIVATE  ../include)


llvm_map_components_to_libnames(llvm_libs Core Support)


target_link_libraries(
        VPlanAnalysis
        PRIVATE
        ${llvm_libs}
        )
