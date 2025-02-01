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

message (STATUS "\n-- Setting components")

set (
  COMPONENTS
    logger
)

foreach( COMPONENT ${COMPONENTS})
  add_subdirectory (
    ${COMPONENT}
  )
endforeach()

message (
  STATUS ""
)