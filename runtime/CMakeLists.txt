cmake_minimum_required(VERSION 3.15)

project(go-module)
set(PROJECT_MODULE_NAME go-module)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_target_properties(PROPERTIES PREFIX "")

# configure smf
set(SMF_MANAGE_DEPS ON CACHE "" INTERNAL FORCE)
set(SMF_BUILD_PROGRAMS OFF CACHE "" INTERNAL FORCE)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.h" "src/*.hpp" "src/*.cpp"
        "src/events/*.h" "src/events/*.hpp" "src/events/*.cpp")
file(GLOB_RECURSE PROJECT_FBS_FILES "src/fbs/*.fbs")



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

MESSAGE(STATUS "Flags:" ${CMAKE_CXX_FLAGS_RELEASE})

# smf dependency
add_subdirectory(vendors/smf)

# cpp-sdk dependency
include("vendors/cpp-sdk/CMakeLists.txt")
include_directories("vendors/cpp-sdk")

# go-module headers
include_directories(
        "src"
)

# smf fbs gen
target_include_directories(${PROJECT_MODULE_NAME} ${CMAKE_CURRENT_BINARY_DIR})

smfc_gen(CPP ${PROJECT_MODULE_NAME} kvstore_fbs
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    SOURCES ${PROJECT_FBS_FILES}
)

add_library(
        ${PROJECT_MODULE_NAME} SHARED
        ${PROJECT_SOURCE_FILES}
)
add_dependencies(${PROJECT_MODULE_NAME} alt-sdk)
target_link_libraries(${PROJECT_MODULE_NAME} PRIVATE smf::smf)