cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# all files required for the standard election executable to be built
add_library(election
    AuditLog.cpp
    Candidate.cpp
    CPLCandidate.cpp
    CPLElectionData.cpp
    CPLParty.cpp
    ElectionData.cpp
    ElectionDataParser.cpp
    OPLCandidate.cpp
    OPLElectionData.cpp
    OPLParty.cpp
    Party.cpp
)