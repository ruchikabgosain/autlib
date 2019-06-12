cmake_minimum_required(VERSION 3.0)

project(autlib DESCRIPTION "Handling .aut files")

option(BUILD_SHARED "Build also a shared library" 												ON)
option(BUILD_DOC 		"Build the docs (requires Doxygen)" 									ON)
option(BUILD_TESTS 	"Build unit tests (requires internet connectivity)" 	ON)
option(COVERAGE  		"Set to ON to build with code coverage" 							ON)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
	message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file).
		Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

### Build type ###
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DDEBUG)
endif()

message("Build ${CMAKE_BUILD_TYPE}")

### Project version number
set(VERSION_MAJOR 0 CACHE STRING "Project major version.")
set(VERSION_MINOR 1 CACHE STRING "Project minor version.")
# add_definitions(-D__AUTLIB_VER=${VERSION_MAJOR}.${VERSION_MINOR})
# add_definitions(-D__AUTLIB_MAJOR=${VERSION_MAJOR})
# add_definitions(-D__AUTLIB_MINOR=${VERSION_MAJOR})

### includes ###
set(INCLUDE_DIR include)

### Compiler Flags ###
set(GCC_FLAGS 	"-E")
set(CLANG_FLAGS "-E")
set(ICC_FLAGS 	"")
set(MSVC_FLAGS 	"")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  message("Compiling with Clang")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  message("Compiling with GNU")
  # set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  message("Compiling with Intel")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  message("Compiling with MSVC")
endif()

## Build the docs  ##
if(BUILD_DOC)
	add_subdirectory(docs)
endif()

###  COVERAGE SETTINGS  ###
add_library(coverage_config INTERFACE)
if(COVERAGE)
  message("BUILDING WITH COVERAGE")
  target_compile_options(coverage_config INTERFACE
  -O0        # no optimization
  -g         # generate debug info
  --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif(COVERAGE)

## Build the lib   ##
add_subdirectory(src)

## Build the tests ##
if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()
