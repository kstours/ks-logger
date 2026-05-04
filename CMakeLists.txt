cmake_minimum_required(VERSION 3.14)
project(ks-logger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory("external/glfw")

add_library(imgui_setup STATIC
    "external/imgui-docking/imgui.cpp"
    "external/imgui-docking/imgui_draw.cpp"
    "external/imgui-docking/imgui_widgets.cpp"
    "external/imgui-docking/imgui_tables.cpp"
    "external/imgui-docking/imgui_demo.cpp"
    "external/imgui-docking/backends/imgui_impl_glfw.cpp"
    "external/imgui-docking/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(imgui_setup PUBLIC 
    "external/imgui-docking"
    "external/imgui-docking/backends"
    "external/glfw/include"
)

add_library(ks_logger_lib STATIC 
    "src/ks_logger.cpp" 
    "include/ks_logger.h" 
    "src/ui/window_frame/window_frame.cpp" 
    "src/ui/window_frame/window_frame.h"
)

target_include_directories(ks_logger_lib PUBLIC "include" "src")
target_include_directories(ks_logger_lib PRIVATE "src/window_frame")

target_link_libraries(ks_logger_lib PUBLIC imgui_setup glfw OpenGL::GL)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples/main.cpp")
    add_executable(KSLogger_Example "examples/main.cpp")
    target_link_libraries(KSLogger_Example PRIVATE ks_logger_lib)
    if(APPLE)
        target_link_libraries(KSLogger_Example PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
    endif()

    if(WIN32 AND MINGW)
        target_link_options(KSLogger_Example PRIVATE "-static-libgcc" "-static-libstdc++" "-static")
    endif()
endif()