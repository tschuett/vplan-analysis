add_executable(vplan
           main.cpp
           )

target_include_directories(vplan PRIVATE  ../include)


llvm_map_components_to_libnames(llvm_libs Support)

target_link_libraries(vplan
        PRIVATE
        VPlanAnalysis
)


#         ${llvm_libs}
