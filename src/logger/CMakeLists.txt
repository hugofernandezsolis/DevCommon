################################################################################
#########                      COMPONENT SETTINGS                      #########
################################################################################
### Add comment here.
################################################################################

set (
  COMPONENT_DEPENDENCIES
)

file (
  GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library (
  ${COMPONENT_LIB} OBJECT
)

target_include_directories(
  ${COMPONENT_LIB}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_sources (
  ${COMPONENT_LIB}
    PRIVATE ${SRC_FILES}
)

target_link_libraries (
  ${COMPONENT_LIB}
    PRIVATE ${COMPONENT_DEPENDENCIES}
)

if (ENABLE_TESTS)
  add_subdirectory (
    tests
  )
endif ()

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include
)
