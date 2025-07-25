cmake_minimum_required(VERSION 3.15)
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()

project(NoSignal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

enable_testing()
# 添加 src 目录到 include path
include_directories(${CMAKE_SOURCE_DIR}/src)

# 分别定义客户端和服务端源文件
file(GLOB_RECURSE NoSignal_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cxx
    ${CMAKE_SOURCE_DIR}/src/*.cc
)
set(NoSignal_CLIENT_SOURCES ${NoSignal_SOURCES})
list(REMOVE_ITEM NoSignal_CLIENT_SOURCES "${CMAKE_SOURCE_DIR}/src/server_main.cpp")

set(NoSignal_SERVER_SOURCES ${NoSignal_SOURCES})
list(REMOVE_ITEM NoSignal_SERVER_SOURCES "${CMAKE_SOURCE_DIR}/src/client_main.cpp")
list(FILTER NoSignal_SERVER_SOURCES EXCLUDE REGEX "${CMAKE_SOURCE_DIR}src/client/.*")

# 客户端可执行文件
add_executable(NoSignal ${NoSignal_CLIENT_SOURCES})
target_link_libraries(NoSignal PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)
target_link_libraries(NoSignal PRIVATE fmt::fmt)
target_link_libraries(NoSignal PRIVATE magic_enum::magic_enum)

# 服务端可执行文件
add_executable(NoSignalServer ${NoSignal_SERVER_SOURCES})
target_link_libraries(NoSignalServer PRIVATE fmt::fmt)
target_link_libraries(NoSignal PRIVATE magic_enum::magic_enum)

file(GLOB_RECURSE NoSignal_TESTS
    test/*.cpp
    test/*.c
    test/*.cxx
    test/*.cc
)
#add_executable(tests ${NoSignal_TESTS} ${NoSignal_SOURCES})
#target_link_libraries(tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
#add_test(NAME tests COMMAND tests)