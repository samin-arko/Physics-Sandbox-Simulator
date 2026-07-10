cmake_minimum_required(VERSION 3.10)
project(RaylibPhysicsSimulator CXX)

# Tell the project to use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define paths to your isolated Raylib installation
set(RAYLIB_INCLUDE_DIR "C:/raylib/raylib/src")
set(RAYLIB_LIB_DIR "C:/raylib/raylib/src")

# Define your executable and its source files
add_executable(${PROJECT_NAME} main.cpp)

# Target Include Directories (Where headers like raylib.h are)
target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_INCLUDE_DIR})

# Find and Link the Raylib Static Library & Windows Dependencies
target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib 
    opengl32 
    gdi32 
    winmm
)