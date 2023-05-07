cmake_minimum_required(VERSION 3.5)


project(Graphics_engine)

add_subdirectory(ext/imgui)
include_directories(ext/imgui)

add_executable(${PROJECT_NAME} WIN32 src/main.cpp src/window.h src/window.cpp src/application.h src/application.cpp src/guiManager.h src/guiManager.cpp src/timer.h src/timer.cpp src/directX.h src/directX.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE d3d11.lib D3DCompiler.lib PUBLIC imgui)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)
