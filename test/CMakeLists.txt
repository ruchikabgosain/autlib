configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Create a libgtest target to be used as a dependency by test programs
# add_library(libgtest IMPORTED STATIC GLOBAL)
# add_dependencies(libgtest gtest)

### UNIT TESTS SETTINGS ###
include_directories(${autlib_SOURCE_DIR}/${INCLUDE_DIR})
set(FILES_DIR ${autlib_SOURCE_DIR}/files)


### UNIT TESTS ###
set( TestList
  test_repr_descriptor
  test_repr_transition
	test_repr_aut
  test_read
)

foreach(test IN ITEMS ${TestList})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} autlib gtest gtest_main coverage_config)
  add_test(NAME ${test} COMMAND ${test})
endforeach()

### COVERAGE ###
add_executable(test_all test_all.cpp)
target_link_libraries(test_all autlib gtest gtest_main coverage_config)

### Scratchpad ###
add_executable(scratchpad scratchpad.c)
target_link_libraries(scratchpad autlib)

add_executable(test_write_aut test_write_aut.cpp)
target_link_libraries(test_write_aut autlib)
