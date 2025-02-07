################################################################################
#########                      COMPONENT SETTINGS                      #########
################################################################################
### Add comment here.
################################################################################
message (STATUS "  Found component: ${COMPONENT}")

file (
  GLOB_RECURSE ${COMPONENT}_SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

target_include_directories (
  ${PROJECT_NAME}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources (
  ${PROJECT_NAME}
    PRIVATE ${${COMPONENT}_SRC_FILES}
)

if (ENABLE_TESTS)
  add_subdirectory (
    tests
  )
endif ()