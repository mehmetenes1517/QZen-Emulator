set(PROJECT_NAME QZenEmulator)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

project(${PROJECT_NAME})

set(LIB_SOURCE
${CMAKE_SOURCE_DIR}/src/ControlUnit.cpp
${CMAKE_SOURCE_DIR}/src/LogicUnit.cpp
${CMAKE_SOURCE_DIR}/src/Memory.cpp
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


