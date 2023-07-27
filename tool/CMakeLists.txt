add_executable(vplan
           main.cpp
           )

target_include_directories(vplan PRIVATE  ../include)

target_link_libraries(vplan
        PRIVATE
        VPlanAnalysis
)
