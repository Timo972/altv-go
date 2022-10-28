# CMakeList.txt: progetto CMake per altv-capi-golang. Includere l'origine e definire
# qui la logica specifica del progetto.
#
cmake_minimum_required (VERSION 3.8)
project(altv-go-capi)

if(WIN32)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/win32")
else()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/linux")
endif()
MESSAGE(STATUS "Compiling altv-go-capi:" ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# Generate c-api header & source files
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/out/capi.h ${CMAKE_CURRENT_BINARY_DIR}/out/capi.c
    COMMAND node ../../../runtime/tools/pkg-capi.js
)
# Copy header to lib directory
# FIXME:
#configure_file(${CMAKE_CURRENT_BINARY_DIR}/out/capi.h ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/../capi.h COPYONLY)

# Aggiungere l'origine all'eseguibile di questo progetto.
add_library (capi STATIC "./out/capi.c" "./out/capi.h")

if ( MSVC )
    set_target_properties(capi PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
    set_target_properties(capi PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
endif ( MSVC )

# TODO: Aggiungere i test e, se necessario, installare le destinazioni.
