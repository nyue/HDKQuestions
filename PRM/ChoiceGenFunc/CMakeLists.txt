hdk_add_library(SOP_ChoiceGenFunc SHARED
  SOP_ChoiceGenFunc.cpp
  SOP_ChoiceGenFunc.h
  )

install(TARGETS
  SOP_ChoiceGenFunc
  DESTINATION
  dso
  )
