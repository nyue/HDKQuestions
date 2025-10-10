set(library_name SOP_ChoiceGenFunc)

houdini_generate_proto_headers(FILES SOP_ChoiceGenFunc.cpp)

add_library(SOP_ChoiceGenFunc SHARED
        SOP_ChoiceGenFunc.cpp
        SOP_ChoiceGenFunc.h
)

target_link_libraries(${library_name} Houdini)

target_include_directories(${library_name} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

houdini_configure_target(${library_name})