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

set(Protobuf_USE_STATIC_LIBS ON)
set(PROTOBUF_IMPORT_DIRS ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.h" "src/*.hpp" "src/*.cpp"
        "src/events/*.h" "src/events/*.hpp" "src/events/*.cpp")
file(GLOB_RECURSE PROJECT_PROTO_FILES "src/*.proto")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

MESSAGE(STATUS "Flags:" ${CMAKE_CXX_FLAGS_RELEASE})
MESSAGE(STATUS "LIB_SUFFIX:" ${CMAKE_FIND_LIBRARY_SUFFIXES})

# protobuf dependency
find_package(Protobuf REQUIRED)

# cpp-sdk dependency
include("vendors/cpp-sdk/CMakeLists.txt")
include_directories("vendors/cpp-sdk")

# go-module headers
include_directories(
        "src"
)

add_library(
        ${PROJECT_MODULE_NAME} SHARED
        ${PROJECT_SOURCE_FILES} ${PROJECT_PROTO_FILES}
)
add_dependencies(${PROJECT_MODULE_NAME} alt-sdk)
target_link_libraries(${PROJECT_MODULE_NAME} PRIVATE ${Protobuf_LIBRARIES})

# include generated proto sources
target_include_directories(${PROJECT_MODULE_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/src ${Protobuf_INCLUDE_DIRS})

# generate protobuf files
protobuf_generate(TARGET ${PROJECT_MODULE_NAME} LANGUAGE cpp)