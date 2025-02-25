SET(LIB_NAME ui)
SET(LIB_OUTNAME octoon-${LIB_NAME})

SET(HEADER_PATH ${OCTOON_PATH_HEADER}/${LIB_NAME})
SET(SOURCE_PATH ${OCTOON_PATH_SOURCE}/${LIB_OUTNAME})

SET(UI_LIST
    ${HEADER_PATH}/imgui.h
    ${SOURCE_PATH}/imgui.cpp
    ${HEADER_PATH}/imgui_system.h
    ${SOURCE_PATH}/imgui_system.cpp
)
SOURCE_GROUP(${LIB_NAME} FILES ${UI_LIST})

IF(OCTOON_BUILD_SHARED_DLL)
	ADD_DEFINITIONS(-DOCTOON_BUILD_DLL_EXPORT)
	ADD_LIBRARY(${LIB_OUTNAME} SHARED ${UI_LIST})
ELSE()
	ADD_DEFINITIONS(-DOCTOON_STATIC)
	ADD_LIBRARY(${LIB_OUTNAME} ${UI_LIST})
ENDIF()

TARGET_LINK_LIBRARIES(${LIB_OUTNAME} PRIVATE imgui)
TARGET_LINK_LIBRARIES(${LIB_OUTNAME} PRIVATE ImGuizmo)
TARGET_LINK_LIBRARIES(${LIB_OUTNAME} PRIVATE octoon-hal)
TARGET_LINK_LIBRARIES(${LIB_OUTNAME} PRIVATE octoon-input)
TARGET_LINK_LIBRARIES(${LIB_OUTNAME} PRIVATE octoon-runtime)

TARGET_INCLUDE_DIRECTORIES(${LIB_OUTNAME} PRIVATE ${OCTOON_PATH_INCLUDE})

SET_TARGET_ATTRIBUTE(${LIB_OUTNAME} "core")