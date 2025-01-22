################################################################################
#########                        TESTS SETTINGS                        #########
################################################################################
### Add comment here.
################################################################################

set (
  COMPONENT_TESTS ${COMPONENT}_tests
)

file (
  GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable (
  ${COMPONENT_TESTS}
    ${TEST_FILES}
)

target_include_directories (
  ${COMPONENT_TESTS}
    PRIVATE ${GTEST_INCLUDE_DIRS}
)

add_test (
  NAME ${COMPONENT_TESTS}
  COMMAND ${COMPONENT_TESTS}
)

target_link_libraries (
  ${COMPONENT_TESTS}
    ${COMPONENT_LIB}
    ${GTEST_LIBS}
)
