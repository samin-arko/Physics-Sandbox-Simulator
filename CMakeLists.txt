cmake_minimum_required(VERSION 3.15)
project(PhysicsSandboxSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/physics.cpp
    src/editor.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_include_directories(${PROJECT_NAME} PRIVATE "C:/raylib/raylib/src")
target_link_libraries(${PROJECT_NAME} PRIVATE "C:/raylib/raylib/src/libraylib.a")

target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32 opengl32)