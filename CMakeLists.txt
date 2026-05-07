cmake_minimum_required(VERSION 3.30)
set(PROJECT_NAME QZenEmulator)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

project(${PROJECT_NAME})

set(LIB_SOURCE
    ${CMAKE_SOURCE_DIR}/src/ControlUnit.cpp
    ${CMAKE_SOURCE_DIR}/src/LogicUnit.cpp
    ${CMAKE_SOURCE_DIR}/src/Memory.cpp
    ${CMAKE_SOURCE_DIR}/src/Util.cpp
    ${CMAKE_SOURCE_DIR}/src/Assembler/Assembler.cpp
)
add_library(QZenLib ${LIB_SOURCE})

add_executable(CLIVisualizer ${CMAKE_SOURCE_DIR}/Examples/clivisualizer.cpp)
target_link_libraries(CLIVisualizer QZenLib)

add_executable(GPUVisualizer ${CMAKE_SOURCE_DIR}/Examples/gpuvisualizer.cpp)
if(LINUX)
    target_link_libraries(GPUVisualizer QZenLib raylib X11)
else()
    target_link_libraries(GPUVisualizer QZenLib raylib)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/tests/ALU/)
add_executable(ALUUnitTests ${CMAKE_SOURCE_DIR}/tests/ALU/alu_tests.cpp)
target_link_libraries(ALUUnitTests QZenLib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/tests/Assembler/)
add_executable(AssemblerTests ${CMAKE_SOURCE_DIR}/tests/Assembler/assembler_tests.cpp)
target_link_libraries(AssemblerTests QZenLib)
configure_file(${CMAKE_SOURCE_DIR}/tests/Assembler/main.s ${CMAKE_SOURCE_DIR}/Bin/tests/Assembler/main.s)