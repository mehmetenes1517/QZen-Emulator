cmake_minimum_required(VERSION 3.30)
project(QZenEmulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

set(LIB_SOURCE
    src/ControlUnit.cpp
    src/LogicUnit.cpp
    src/Memory.cpp
    src/Util.cpp
    src/Assembler/Assembler.cpp
)
add_library(QZenLib ${LIB_SOURCE})
target_include_directories(QZenLib PUBLIC src)

add_executable(FramebufferVisualizer Examples/framebuffer.cpp)

if(WIN32)
    target_link_libraries(FramebufferVisualizer QZenLib raylib winmm gdi32 opengl32)
elseif(UNIX)
    target_link_libraries(FramebufferVisualizer QZenLib raylib X11)
endif()

add_executable(CLIVisualizer Examples/clivisualizer.cpp)
target_link_libraries(CLIVisualizer QZenLib)

add_executable(ALUUnitTests tests/ALU/alu_tests.cpp)
target_link_libraries(ALUUnitTests QZenLib)
set_target_properties(ALUUnitTests PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin/tests/ALU"
)

add_executable(AssemblerTests tests/Assembler/assembler_tests.cpp)
target_link_libraries(AssemblerTests QZenLib)
set_target_properties(AssemblerTests PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin/tests/Assembler"
)