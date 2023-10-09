message(STATUS "Fetching catch2")
include(FetchContent)

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v2.13.8
)
FetchContent_MakeAvailable(catch2)
