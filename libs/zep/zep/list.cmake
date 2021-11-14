
SET(ZEP_ROOT ${CMAKE_CURRENT_LIST_DIR}/)
SET(ZEP_SOURCE
${ZEP_ROOT}/../m3rdparty/animation/timer.cpp
${ZEP_ROOT}/../m3rdparty/animation/timer.h
${ZEP_ROOT}/../m3rdparty/string/stringutils.cpp
${ZEP_ROOT}/../m3rdparty/string/stringutils.h
${ZEP_ROOT}/../m3rdparty/threadpool/threadutils.h
${ZEP_ROOT}/../m3rdparty/file/archive.h
${ZEP_ROOT}/../m3rdparty/file/archive.cpp
${ZEP_ROOT}/../m3rdparty/file/path.h
${ZEP_ROOT}/../m3rdparty/file/path.cpp
${ZEP_ROOT}/../m3rdparty/logger.h
${ZEP_ROOT}/imgui/display_imgui.cpp
${ZEP_ROOT}/imgui/display_imgui.h
${ZEP_ROOT}/imgui/editor_imgui.cpp
${ZEP_ROOT}/imgui/editor_imgui.h
${ZEP_ROOT}/filesystem.cpp
${ZEP_ROOT}/filesystem.h
${ZEP_ROOT}/editor.cpp
${ZEP_ROOT}/editor.h
${ZEP_ROOT}/splits.cpp
${ZEP_ROOT}/splits.h
${ZEP_ROOT}/buffer.cpp
${ZEP_ROOT}/buffer.h
${ZEP_ROOT}/commands.cpp
${ZEP_ROOT}/commands.h
${ZEP_ROOT}/display.cpp
${ZEP_ROOT}/display.h
${ZEP_ROOT}/tab_window.cpp
${ZEP_ROOT}/tab_window.h
${ZEP_ROOT}/window.cpp
${ZEP_ROOT}/window.h
${ZEP_ROOT}/scroller.cpp
${ZEP_ROOT}/scroller.h
${ZEP_ROOT}/syntax.cpp
${ZEP_ROOT}/syntax.h
${ZEP_ROOT}/syntax_providers.cpp
${ZEP_ROOT}/syntax_providers.h
${ZEP_ROOT}/syntax_rainbow_brackets.cpp
${ZEP_ROOT}/syntax_rainbow_brackets.h
${ZEP_ROOT}/mode.cpp
${ZEP_ROOT}/mode.h
${ZEP_ROOT}/mode_standard.cpp
${ZEP_ROOT}/mode_standard.h
${ZEP_ROOT}/mode_vim.cpp
${ZEP_ROOT}/mode_vim.h
${ZEP_ROOT}/mode_search.cpp
${ZEP_ROOT}/mode_search.h
${ZEP_ROOT}/theme.cpp
${ZEP_ROOT}/theme.h
${ZEP_ROOT}/list.cmake
)

LIST(APPEND SRC_INCLUDE ${ZEP_ROOT})

# IF (BUILD_QT)
# SET(ZEP_SOURCE_QT
#     ${ZEP_ROOT}/src/qt/zepdisplay_qt.cpp
#     ${ZEP_ROOT}/src/qt/zepdisplay_qt.h
#     ${ZEP_ROOT}/src/qt/zepwidget_qt.cpp
#     ${ZEP_ROOT}/src/qt/zepwidget_qt.h
#     )
# SET(ZEP_INCLUDE_QT ${ZEP_ROOT}/src/qt)
# ENDIF()

# IF (BUILD_IMGUI)
# SET(ZEP_SOURCE_IMGUI
    # ${ZEP_ROOT}/imgui/display_imgui.cpp
    # ${ZEP_ROOT}/imgui/display_imgui.h
    # ${ZEP_ROOT}/imgui/editor_imgui.cpp
    # ${ZEP_ROOT}/imgui/editor_imgui.h)
# SET(ZEP_INCLUDE_IMGUI ${ZEP_ROOT}/src/qt)
# ENDIF()

