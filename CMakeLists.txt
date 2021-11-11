cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
# ENABLE CMP0054: Only interpret if() arguments as variables or keywords when unquoted
cmake_policy(SET CMP0054 NEW)
# ENABLE CMP0074: USE *_ROOT PATH variables
cmake_policy(SET CMP0074 NEW)

# Meta information about the project
set(META_PROJECT_NAME        "Needle")
set(META_PROJECT_DESCRIPTION "Unbug with a needle in your hand")
set(META_AUTHOR_ORGANIZATION "Trocious")
set(META_AUTHOR_DOMAIN       "")
set(META_AUTHOR_MAINTAINER   "emptyseth0@gmail.com")
set(META_VERSION_MAJOR       "1")
set(META_VERSION_MINOR       "0")
set(META_VERSION_PATCH       "0")
#set(META_VERSION_REVISION    "<REVISION>")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
#set(META_NAME_VERSION        "${META_PROJECT_NAME} v${META_VERSION} (${META_VERSION_REVISION})")
set(META_CMAKE_INIT_SHA      "<CMAKE_INIT_REVISION>")

string(MAKE_C_IDENTIFIER ${META_PROJECT_NAME} META_PROJECT_ID)
string(TOUPPER ${META_PROJECT_ID} META_PROJECT_ID)
message(${META_PROJECT_NAME} " " ${META_PROJECT_ID})

# Require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE_INIT "RelWithDebInfo")

# set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

project("Needle" LANGUAGES CXX C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

# Find OpenGL
find_package(OpenGL REQUIRED)

# Detect and add GLFW
# find_package(glfw3 3.3 REQUIRED)
set(GLFW_DIR ${LIB_DIR}/glfw-3.3-stable)
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES ON CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

set(SOURCES Main.cpp Needle.cpp GlfwHandler.cpp ImguiHandler.cpp GlTriangle.cpp)

# add_exe needs to happen before link libraries
add_executable(${PROJECT_NAME} ${SOURCES})

set(GLAD_DIR ${LIB_DIR}/glad)
add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PRIVATE ${GLAD_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)

set(DEAR_IMGUI_DIR ${LIB_DIR}/dear_imgui)
add_library(dear_imgui)
target_sources(dear_imgui PRIVATE ${DEAR_IMGUI_DIR}/imgui.cpp 
    ${DEAR_IMGUI_DIR}/imgui_demo.cpp ${DEAR_IMGUI_DIR}/imgui_draw.cpp
    ${DEAR_IMGUI_DIR}/imgui_tables.cpp ${DEAR_IMGUI_DIR}/imgui_widgets.cpp)
target_sources(dear_imgui PRIVATE ${DEAR_IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${DEAR_IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
target_link_libraries(dear_imgui OpenGL::GL glfw ${GLFW_LIBRARIES})
target_include_directories(dear_imgui PRIVATE ${GLFW_DIR}/include ${DEAR_IMGUI_DIR} ${DEAR_IMGUI_DIR}/backends)

set(GLM_DIR ${LIB_DIR}/glm-0.9.7)

set(STB_IMAGE ${LIB_DIR}/stb)

include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw ${GLFW_LIBRARIES} glad dear_imgui ${CMAKE_DL_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include
    ${DEAR_IMGUI_DIR} ${DEAR_IMGUI_DIR}/backends ${GLM_DIR} ${STB_IMAGE})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
# Check if we need DEBUG compiler definition
string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if(cmake_build_type_tolower STREQUAL "debug" OR
    cmake_build_type_tolower STREQUAL "relwithdebinfo")
    target_compile_definitions(${PROJECT_NAME} PRIVATE NEEDLE_DEBUG)
    message("Enabling NEEDLE_DEBUG mode")
endif()

