cmake_minimum_required(VERSION 3.10)
project(FileSystemCli)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_REQUIRED True)

set(SOURCES
src/main.cpp
src/filesystem/Filesystem.cpp
src/cli/CommandParser.cpp
)

set(HEADERS
src/filesystem/Filesystem.h
src/cli/CommandParser.h
)

add_executable(fileSystemCli ${SOURCES} ${HEADERS})

target_include_directories(fileSystemCli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
