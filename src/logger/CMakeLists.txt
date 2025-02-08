################################################################################
#########                      COMPONENT SETTINGS                      #########
################################################################################
### Add comment here.
################################################################################
message (STATUS "  Found component: ${COMPONENT}")

add_library (
  ${COMPONENT_LIB} ${LIB_TYPE}
)

file (
  GLOB_RECURSE ${COMPONENT}_SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

target_include_directories (
  ${COMPONENT_LIB}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources (
  ${COMPONENT_LIB}
    PRIVATE ${${COMPONENT}_SRC_FILES}
)

if (ENABLE_TESTS)
  add_subdirectory (
    tests
  )
endif ()


target_link_libraries (
  ${PROJECT_NAME}
    INTERFACE ${COMPONENT_LIB}
)

install(
  TARGETS ${COMPONENT_LIB}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)