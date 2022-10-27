cmake_minimum_required(VERSION 3.15)

project(go-module)
set(PROJECT_MODULE_NAME go-module)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_target_properties(PROPERTIES PREFIX "")

if ("${GO_MODULE_VERSION}" STREQUAL "")
add_definitions(-DGO_MODULE_VERSION="DEBUG")
else()
add_definitions(-DGO_MODULE_VERSION="${GO_MODULE_VERSION}")
endif()

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.h" "src/*.hpp" "src/*.cpp"
        "src/events/*.h" "src/events/*.hpp" "src/events/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# cpp-sdk dependency
include("vendors/cpp-sdk/CMakeLists.txt")
include_directories("vendors/cpp-sdk")

# go-module headers
include_directories(
        "src"
)

add_library(
        ${PROJECT_MODULE_NAME} SHARED
        ${PROJECT_SOURCE_FILES}
)
add_dependencies(${PROJECT_MODULE_NAME} alt-sdk)