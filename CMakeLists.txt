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


################################################################################
#########                         C++ SETTINGS                         #########
################################################################################
### This section sets up C++ compilation standards and flags, as well as any
### additional compile options such as warnings.
################################################################################

set (
  CMAKE_CXX_STANDARD 17
)

set (
  CMAKE_CXX_STANDARD_REQUIRED ON
)

set (
  CMAKE_CXX_FLAGS_DEBUG "-O0 -g"
)

set (
  CMAKE_CXX_FLAGS_RELEASE "-O3"
)

add_compile_options (
  -Wall
  -Wextra
  -Wpedantic
)


################################################################################
#########                      COVERAGE SETTINGS                       #########
################################################################################
### This section adds a coverage option and, if enabled, sets compiler/linker
### flags to generate coverage information. It also creates a custom target
### to run lcov and genhtml.
################################################################################

option (
  ENABLE_TESTS "Enable building tests with GoogleTest" OFF
)

if (ENABLE_TESTS)
  enable_testing ()
endif ()

option (
  ENABLE_COVERAGE "Enable coverage generation (gcov/lcov)" OFF
)

if (ENABLE_COVERAGE)

    set (
      CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g"
    )

    set (
      CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage"
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

add_library(
  ${PROJECT_NAME} INTERFACE
)

set (
  COMPONENTS
    logger
)

add_subdirectory (
  src
)

foreach( COMPONENT ${COMPONENTS})
  target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/${COMPONENT}/include>
    $<INSTALL_INTERFACE:include>
  )
endforeach()


message (
  STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}"
)

message (
  STATUS "Build mode: ${CMAKE_BUILD_TYPE}"
)

message (
  STATUS "Testing enabled: ${ENABLE_TESTS}"
)

message (
  STATUS "Coverage enabled: ${ENABLE_COVERAGE}"
)

message (
  STATUS ""
)


################################################################################
#########                       INSTALL SETTINGS                       #########
################################################################################
### This section defines the installation requirements.
################################################################################

set (
  TARGET_LIBS ""
)

foreach(COMPONENT ${COMPONENTS})
  list(APPEND TARGET_LIBS ${COMPONENT}_lib)
endforeach()

install (
  TARGETS ${PROJECT_NAME} ${TARGET_LIBS}
  EXPORT  ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install (
  EXPORT      ${PROJECT_NAME}Targets
  FILE        ${PROJECT_NAME}Targets.cmake
  NAMESPACE   ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME}
)

include (CMakePackageConfigHelpers)

configure_package_config_file (
  cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
  PATH_VARS CMAKE_INSTALL_PREFIX
)

write_basic_package_version_file (
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install (
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION lib/cmake/${PROJECT_NAME}
)
