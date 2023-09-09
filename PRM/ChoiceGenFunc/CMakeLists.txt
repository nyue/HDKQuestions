houdini_generate_proto_headers( OUTPUT_VAR proto_headers
  FILES SOP_ChoiceGenFunc.cpp )

message("proto_headers = ${proto_headers}")

add_library( SOP_ChoiceGenFunc SHARED
  SOP_ChoiceGenFunc.cpp
  SOP_ChoiceGenFunc.h
  )

target_link_libraries( SOP_ChoiceGenFunc Houdini )

install(TARGETS
  SOP_ChoiceGenFunc
  DESTINATION
  dso
  )
