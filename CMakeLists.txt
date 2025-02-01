################################################################################
#########                        CMAKE SETTINGS                        #########
################################################################################
### This section configures basic CMake settings, including the minimum version
### required and the default build type if none is provided.
################################################################################

cmake_minimum_required (
  VERSION 3.30
)

set (
  CMAKE_POSITION_INDEPENDENT_CODE ON
)

if (NOT CMAKE_BUILD_TYPE)
    set (
      CMAKE_BUILD_TYPE "Debug"
      CACHE STRING "Default build type" 
      FORCE
    )
endif()

set (
  LIB_TYPE "STATIC"
  CACHE STRING "Define library type: STATIC or SHARED"
  FORCE
)

set_property (
  CACHE LIB_TYPE 
  PROPERTY STRINGS "STATIC" "SHARED"
)

if(NOT (LIB_TYPE STREQUAL "STATIC" OR LIB_TYPE STREQUAL "SHARED"))
  set (
    LIB_TYPE "STATIC"
  )
endif()

option (
  ENABLE_TESTS "Enable building tests with GoogleTest"
  OFF
)

option (
  ENABLE_COVERAGE "Enable coverage generation (gcov/lcov)"
  OFF
)


################################################################################
#########                       PROJECT SETTINGS                       #########
################################################################################
### This section defines the project name, version, languages, and logs some
### useful information about the build process.
################################################################################

project (
  DevCommon
    VERSION 1.0
    LANGUAGES CXX
)

add_library (
  ${PROJECT_NAME} ${LIB_TYPE}
    ${CMAKE_CURRENT_LIST_DIR}/src/.dummy.cpp
)


################################################################################
#########                         C++ SETTINGS                         #########
################################################################################
### This section sets up C++ compilation standards and flags, as well as any
### additional compile options such as warnings.
################################################################################

set (
  CMAKE_CXX_STANDARD_REQUIRED ON
)

target_compile_features (
  ${PROJECT_NAME} 
    PUBLIC cxx_std_17
)

target_compile_options (
  ${PROJECT_NAME}
    PRIVATE -Wall -Wextra -Wpedantic
)

target_compile_options (
  ${PROJECT_NAME}
    PRIVATE
      $<$<CONFIG:Debug>:-O0 -g>
      $<$<CONFIG:Release>:-O3>
)


################################################################################
#########                        TEST SETTINGS                         #########
################################################################################
### Add comment here.
################################################################################

if (ENABLE_TESTS)
  enable_testing ()
endif ()


################################################################################
#########                      COVERAGE SETTINGS                       #########
################################################################################
### This section adds a coverage option and, if enabled, sets compiler/linker
### flags to generate coverage information. It also creates a custom target
### to run lcov and genhtml.
################################################################################


if (ENABLE_COVERAGE)
  target_compile_options (
    ${PROJECT_NAME}
      PRIVATE --coverage -O0 -g
  )

  target_link_options (
    ${PROJECT_NAME}
      PRIVATE --coverage
  )

    add_custom_target (
      coverage
        COMMAND ${CMAKE_COMMAND} -E remove -f coverage.info
        COMMAND lcov --capture --directory . --output-file coverage.info
        COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info
        COMMAND genhtml coverage.info --output-directory coverage
        COMMAND ${CMAKE_COMMAND} -E echo "Coverage report generated in the 'coverage' directory."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage report with lcov and genhtml..."
    )
endif ()

add_subdirectory (
  src
)


################################################################################
#########                    INSTALLATION SETTINGS                     #########
################################################################################
### Add comment here.
################################################################################

include (GNUInstallDirs)

install (
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install (
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Config.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)


################################################################################
#########                        CMAKE RESULTS                         #########
################################################################################
### Add comment here.
################################################################################

message (STATUS "Library type:     ${LIB_TYPE}")
message (STATUS "Coverage enabled: ${ENABLE_COVERAGE}")
message (STATUS "Testing enabled:  ${ENABLE_TESTS}")
message (STATUS "")