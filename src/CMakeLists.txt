################################################################################
#########                      EXTERNAL LIBRARIES                      #########
################################################################################
### Add comment here.
################################################################################

include (FetchContent)

message (
  STATUS "\n-- Checking external packages"
)

find_package (
  GTest QUIET
)

if (GTest_FOUND)
    message (
      STATUS "  Found GTest in the system"
    )
else ()
    message (
      STATUS "  Unable to find GTest in the system. Fetching from github"
    )

    FetchContent_Declare (
      googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main
    )
    FetchContent_MakeAvailable (googletest)
endif ()

set (
  GTEST_LIBS
    GTest::GTest
    GTest::Main
)


################################################################################
#########                      PROJECT COMPONENTS                      #########
################################################################################
### Add comment here.
################################################################################

message (
  STATUS "\n-- Configuring components"
)

foreach( COMPONENT ${COMPONENTS})
  set (
    COMPONENT_LIB ${COMPONENT}_lib
  )

  message (
    STATUS "  Configuring ${COMPONENT} component"
  )
  add_subdirectory (
    ${COMPONENT}
  )
  target_link_libraries (
    ${PROJECT_NAME}
      INTERFACE ${COMPONENT_LIB}
  )
endforeach()

message (
  STATUS ""
)