project( LSDs )
cmake_minimum_required( VERSION 2.8.3 )

set( CMAKE_INCLUDE_CURRENT_DIR ON )
include_directories( ${CMAKE_SOURCE_DIR}/ )
include_directories( ${CMAKE_BINARY_DIR}/ )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

configure_file(
    "${PROJECT_SOURCE_DIR}/Configs.h.in"
    "${PROJECT_BINARY_DIR}/Configs.h" )

add_subdirectory( src )
