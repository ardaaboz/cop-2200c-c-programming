cmake_minimum_required(VERSION 3.31)
project(physics_simulation_with_ai C)

set(CMAKE_C_STANDARD 11)

add_executable(physics_simulation_with_ai gemini.c)

target_include_directories(physics_simulation_with_ai PRIVATE
        D:/MSYS2/mingw64/include
)

target_link_libraries(physics_simulation_with_ai
        D:/MSYS2/mingw64/lib/libraylib.a
        glfw3
        opengl32
        gdi32
        winmm
)

