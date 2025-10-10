add_executable(cvexsample
        cvexsample.cpp
)

add_executable(simple
        simple.cpp
)

target_link_libraries(cvexsample Houdini)

target_link_libraries(simple Houdini)
