################################################################################
#########                      COMPONENT SETTINGS                      #########
################################################################################
### Add comment here.
################################################################################
message (STATUS "  Found component: ${COMPONENT}")


set (
  COMPONENT_LIB ${COMPONENT}_lib
)

add_library (
  ${COMPONENT_LIB} INTERFACE
)

file (
  GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

target_include_directories (
  ${COMPONENT_LIB}
    INTERFACE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
)

target_sources (
  ${COMPONENT_LIB}
    PRIVATE ${SRC_FILES}
)

target_link_libraries (
  ${PROJECT_NAME}
    PUBLIC ${COMPONENT_LIB}
)

if (ENABLE_TESTS)
  add_subdirectory (
    tests
  )
endif ()

include (GNUInstallDirs)

install (
  TARGETS ${COMPONENT_LIB}
  EXPORT ${PROJECT_NAME}Targets
)

install (
  DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)