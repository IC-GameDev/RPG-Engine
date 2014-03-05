# This file is part of the :(){ :|:& };:'s project
# Licensing information can be found in the LICENSE file
# (C) 2014 :(){ :|:& };:. All rights reserved.

cmake_minimum_required(VERSION 2.8)
project(rpg)

# Include modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

# Set default build type
if(CMAKE_BUILD_TYPE STREQUAL "")
    # CMake defaults to leaving CMAKE_BUILD_TYPE empty so default to
    # building debug symbols
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

# Set install location
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/bin")

# Make sure executables are placed in the install directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX})
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_INSTALL_PREFIX})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_INSTALL_PREFIX})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_INSTALL_PREFIX})
endforeach()

# Dependency directories for Win32
set(GLEW_ROOT_DIR "${DEPENDENCIES_DIR}/glew")
set(GLM_ROOT_DIR "${DEPENDENCIES_DIR}/glm")
set(LUA_DIR "${DEPENDENCIES_DIR}/lua")
set(RAPIDJSON_ROOT_DIR "${DEPENDENCIES_DIR}/rapidjson")

# Dependencies
include_directories(${CMAKE_SOURCE_DIR}/src)
set(DEPENDENCIES_DIR "./dependencies/" CACHE STRING "Directory to an extracted dependencies package")
set(GLEW_USE_STATIC_LIBS ON)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(Lua REQUIRED)
find_package(RapidJSON REQUIRED)
set(INCLUDES ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${LUA_INCLUDE_DIR} ${RAPIDJSON_INCLUDE_DIR})
set(LIBS ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${LUA_LIBRARIES})
add_definitions(${GLEW_DEFINITIONS})

# Game logic & entity system
file(GLOB GAME_SOURCES "src/game/*.cc")
file(GLOB GAME_HEADERS "src/game/*.h")
set(SOURCES ${SOURCES} ${GAME_SOURCES})
set(HEADERS ${HEADERS} ${GAME_HEADERS})
source_group(game FILES ${GAME_SOURCES} ${GAME_HEADERS})

# Common library
file(GLOB CORE_SOURCES "src/core/*.cc")
file(GLOB CORE_HEADERS "src/core/*.h")
set(SOURCES ${SOURCES} ${CORE_SOURCES})
set(HEADERS ${HEADERS} ${CORE_HEADERS})
source_group(lib FILES ${CORE_SOURCES} ${CORE_HEADERS})

# Renderer
file(GLOB RENDERER_SOURCES "src/renderer/*.cc")
file(GLOB RENDERER_HEADERS "src/renderer/*.h")
set(SOURCES ${SOURCES} ${RENDERER_SOURCES})
set(HEADERS ${HEADERS} ${RENDERER_HEADERS})
source_group(renderer FILES ${RENDERER_SOURCES} ${RENDERER_HEADERS})

# Resource Manager
file(GLOB RSMNGR_SOURCES "src/rsmngr/*.cc")
file(GLOB RSMNGR_HEADERS "src/rsmngr/*.h")
set(SOURCES ${SOURCES} ${RSMNGR_SOURCES})
set(HEADERS ${HEADERS} ${RSMNGR_HEADERS})
source_group(rsmngr FILE ${RSMNGR_SOURCES} ${RSMNGR_HEADERS})

# System
if(WIN32)
    file(GLOB SYS_PLATFORM_SOURCES "src/sys/windows/*.cc")
    file(GLOB SYS_PLATFORM_HEADERS "src/sys/windows/*.h")
    add_definitions(-DR_WINDOWS)
    set(FLAGS WIN32)
elseif(APPLE)
    FILE(GLOB SYS_PLATFORM_SOURCES "src/sys/mac/*.cc")
    FILE(GLOB SYS_PLATFORM_HEADERS "src/sys/mac/*.h")
    add_definitions(-DR_MAC)
    set(FLAGS MACOSX_BUNDLE)
else()
    FILE(GLOB SYS_PLATFORM_SOURCES "src/sys/linux/*.cc")
    FILE(GLOB SYS_PLATFORM_HEADERS "src/sys/linux/*.h")
    add_definitions(-DR_LINUX)
    set(LIBS ${LIBS} X11 Xxf86vm pthread)
    set(FLAGS)
endif()
file(GLOB SYS_SOURCES "src/sys/*.cc")
file(GLOB SYS_HEADERS "src/sys/*.h")
set(SOURCES ${SOURCES} ${SYS_SOURCES} ${SYS_PLATFORM_SOURCES})
set(HEADERS ${HEADERS} ${SYS_HEADERS} ${SYS_PLATFORM_HEADERS})
source_group(sys FILES ${SYS_SOURCES} ${SYS_HEADERS})
source_group(sys\\platform FILES ${SYS_PLATFORM_SOURCES} ${SYS_PLATFORM_HEADERS})

# Create vcproj.user file for Visual Studio to set up working directory
# when running from the IDE
function(create_vcproj_userfile TARGETNAME)
  if(MSVC)
    configure_file(
          ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Templates/VisualStudioUserFile.vcproj.user.in
          ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.vcproj.user
          @ONLY)
    configure_file(
          ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Templates/VisualStudioUserFile.vcxproj.user.in
          ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.vcxproj.user
          @ONLY)
  endif()
endfunction(create_vcproj_userfile)

# Compiler specifics
if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-DR_VCC)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-DR_GCC)
    SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-DR_CLANG)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -march=nocona")
endif()

# Executable
include_directories(${INCLUDES})
add_executable(rpg ${FLAGS} ${SOURCES} ${HEADERS})
target_link_libraries(rpg ${LIBS})
create_vcproj_userfile(rpg)
