cmake_minimum_required(VERSION 3.21.1)
project(fak VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/mainWindow.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)

if(ENABLE_DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif()

add_custom_target(
    clang-format
    COMMAND clang-format --dry-run -Werror ${SOURCES}
)
