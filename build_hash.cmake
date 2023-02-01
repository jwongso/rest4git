set(rest4git "rest4git")
set(USER $ENV{USER})

find_package(Git)
if(NOT GIT_FOUND)
    message(STATUS "git executable not found")
endif()

set(GIT_ARGS --git-dir " " ${PROJECT_SOURCE_DIR}/.git " " --work-tree " " ${PROJECT_SOURCE_DIR})
EXEC_PROGRAM(${GIT_EXECUTABLE} ARGS ${GIT_ARGS} " " rev-parse --short HEAD OUTPUT_VARIABLE GIT_HASH)
EXEC_PROGRAM(${GIT_EXECUTABLE} ARGS ${GIT_ARGS} " " diff-index --name-only HEAD -- OUTPUT_VARIABLE GIT_UNCOMMITTED_CHANGES)

if("${GIT_UNCOMMITTED_CHANGES}" STREQUAL "")
    set(GIT_HASH_DIRTY ${GIT_HASH})
else()
    set(GIT_HASH_DIRTY ${GIT_HASH}-dirty)
endif()

if("${GIT_HASH_DIRTY}" STREQUAL "")
    set(GIT_HASH_DIRTY "unknown_hash")
endif()

set(rest4git_HASH ${rest4git}-${GIT_HASH_DIRTY}-${USER})

message(STATUS "Build hash: " ${rest4git_HASH})