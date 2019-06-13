include_directories(${autlib_SOURCE_DIR}/${INCLUDE_DIR})

### Flex/Bison ###
find_package(FLEX)
if(NOT FLEX_FOUND)
	message(SEND_ERROR "Flex not found")
endif()

find_package(BISON)
if(NOT BISON_FOUND)
	message(SEND_ERROR "Bison not found")
endif()

flex_target(scanner ${autlib_SOURCE_DIR}/src/read/aut.l 
  ${autlib_SOURCE_DIR}/src/read/_scanner_.c 
  DEFINES_FILE ${autlib_SOURCE_DIR}/src/read/_scanner_.h
)

bison_target(parser ${autlib_SOURCE_DIR}/src/read/aut.y
  ${autlib_SOURCE_DIR}/src/read/_parser_.c 
  COMPILE_FLAGS " -v --report=state --report-file=report.bison"
  DEFINES_FILE ${autlib_SOURCE_DIR}/src/read/_parser_.h
)

add_flex_bison_dependency(scanner parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE SOURCES "*.c")

# SET_SOURCE_FILES_PROPERTIES(${SOURCES} PROPERTIES LANGUAGE CXX )

#
message("-- FLEX source : "  ${FLEX_scanner_OUTPUTS})
message("-- BISON source : " ${BISON_parser_OUTPUTS})

#build static autlib
add_library(autlib STATIC ${SOURCES} ${FLEX_scanner_OUTPUTS} ${BISON_parser_OUTPUTS})
set_target_properties(autlib PROPERTIES PREFIX "")
set_target_properties(autlib PROPERTIES OUTPUT_NAME "autlib")
set_target_properties(autlib PROPERTIES SUFFIX ".a")
set_target_properties(autlib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/)
if (COVERAGE)
  target_link_libraries(autlib coverage_config)
endif()

#build shared autlib
if (${BUILD_SHARED})
  add_library(autlib_shared SHARED ${SOURCES} ${FLEX_scanner_OUTPUTS} ${BISON_parser_OUTPUTS})
  if (COVERAGE)
    target_link_libraries(autlib_shared coverage_config)
  endif(COVERAGE)
	set_target_properties(autlib_shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
  set_target_properties(autlib_shared PROPERTIES PREFIX "")
  set_target_properties(autlib_shared PROPERTIES OUTPUT_NAME "autlib")
  set_target_properties(autlib_shared PROPERTIES SUFFIX ".so")
  set_target_properties(autlib_shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/)
endif()
