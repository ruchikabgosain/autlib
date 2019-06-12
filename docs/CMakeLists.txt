find_package(Doxygen)
if(DOXYGEN_FOUND)
  message("Doxygen build started")
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_GENERATE_MAN YES)

  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

  message(${CMAKE_CURRENT_SOURCE_DIR})
  add_custom_target( doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    COMMENT "Generating documentation with Doxygen"
    VERBATIM )
else(DOXYGEN_FOUND)
  message("Building Documentation skipped. Doxygen not found.")
endif(DOXYGEN_FOUND)
