# CMake minimum version
cmake_minimum_required(VERSION 2.4)

# use new policy
cmake_policy(SET CMP0046 NEW)
cmake_policy(SET CMP0003 NEW)

# enable Win32 resource
ENABLE_LANGUAGE(RC)

# include directories
include_directories(../include)

#
# language options
#
option(LANGUAGE_EN_US "Use English" ON)
option(LANGUAGE_IT_IT "Use Italian" ON)
option(LANGUAGE_JA_JP "Use Japanese" ON)
option(LANGUAGE_ZH_CN "Use Chinese" ON)

set(LANG_DEFS "")
if (LANGUAGE_EN_US)
    add_definitions(-DLANGUAGE_EN_US)
    list(APPEND LANG_DEFS -DLANGUAGE_EN_US)
endif()
if (LANGUAGE_IT_IT)
    add_definitions(-DLANGUAGE_IT_IT)
    list(APPEND LANG_DEFS -DLANGUAGE_IT_IT)
endif()
if (LANGUAGE_JA_JP)
    add_definitions(-DLANGUAGE_JA_JP)
    list(APPEND LANG_DEFS -DLANGUAGE_JA_JP)
endif()
if (LANGUAGE_ZH_CN)
    add_definitions(-DLANGUAGE_ZH_CN)
    list(APPEND LANG_DEFS -DLANGUAGE_ZH_CN)
endif()

# EGA
subdirs(../EGA)

# RisohEditor.exe
add_executable(RisohEditor WIN32 
    PackedDIB.cpp
    Res.cpp
    RisohEditor.cpp
    RisohEditor_res.rc
    res/Manifest_1.manifest)
target_link_libraries(RisohEditor libega comctl32 msimg32 winmm gdiplus vfw32 oledlg msimg32 advapi32 shlwapi)
target_compile_definitions(RisohEditor PRIVATE -DUNICODE -D_UNICODE)

# RisohEditorPortable.exe
add_executable(RisohEditorPortable WIN32 
    PackedDIB.cpp
    Res.cpp
    RisohEditor.cpp
    RisohEditor_res.rc
    res/Manifest_1.manifest)
target_link_libraries(RisohEditorPortable libega comctl32 msimg32 winmm gdiplus vfw32 oledlg msimg32 advapi32 shlwapi)
target_compile_definitions(RisohEditorPortable PRIVATE -DPORTABLE -DUNICODE -D_UNICODE)

# resource object extension
if (MSVC)
    set(DOTRES ".res")
    add_definitions(-DMSVC=1)
else()
    set(DOTRES ".o")
    list(APPEND CMAKE_CXX_LINK_FLAGS -municode)
endif()

# use Unicode
add_definitions(-DUNICODE=1 -D_UNICODE=1)

## messagetables.res or messagetables.o
#add_custom_target(messagetables ALL
#    mcdx ${CMAKE_CURRENT_SOURCE_DIR}/RisohEditor_res.rc --preprocessor=${CMAKE_SOURCE_DIR}\\data\\bin\\cpp.exe ${LANG_DEFS} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/messagetables${DOTRES}
#    DEPENDS mcdx ${CMAKE_CURRENT_SOURCE_DIR}/RisohEditor_res.rc
#    BYPRODUCTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/messagetables${DOTRES}
#    COMMENT "mcdx ${CMAKE_CURRENT_SOURCE_DIR}/RisohEditor_res.rc --preprocessor=${CMAKE_SOURCE_DIR}\\data\\bin\\cpp.exe ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/messagetables${DOTRES}"
#    VERBATIM)
#add_dependencies(RisohEditor messagetables)
#add_dependencies(messagetables mcdx)
#set_target_properties(RisohEditor PROPERTIES LINK_FLAGS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/messagetables${DOTRES})

# do statically link
set_target_properties(RisohEditor PROPERTIES LINK_SEARCH_START_STATIC 1)
set_target_properties(RisohEditor PROPERTIES LINK_SEARCH_END_STATIC 1)
