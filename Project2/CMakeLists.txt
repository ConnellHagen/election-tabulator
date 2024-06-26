cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)

enable_testing()

# list all files that need to be included for the testing suite
add_executable(test_suite
    testing/AuditLogUnitTest.cpp
    testing/CandidateUnitTest.cpp
    testing/CPLCandidateUnitTest.cpp
    testing/CPLElectionDataUnitTest.cpp
    testing/CPLPartyUnitTest.cpp
    testing/ElectionDataUnitTest.cpp
    testing/ElectionDataParserUnitTest.cpp
    testing/OPLCandidateUnitTest.cpp
    testing/OPLElectionDataUnitTest.cpp
    testing/OPLPartyUnitTest.cpp
    testing/PartyUnitTest.cpp
    testing/MPOParsingStrategyUnitTest.cpp
    testing/MPOPartyUnitTest.cpp
)

target_link_libraries(
    test_suite
    election
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_suite)
