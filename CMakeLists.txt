cmake_minimum_required (VERSION 3.15)

project (delib
    VERSION 0.0.1
    DESCRIPTION "Divine Engine Library"
    LANGUAGES C CXX
    )

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_C_STANDARD 11)

add_subdirectory (xternal/SDL)
add_subdirectory (xternal/glm)
add_subdirectory (xternal/glfw)

add_library (delib
    src/delib.c++
    src/renderer/software/software_renderer.c++
    src/renderer/opengl/opengl_renderer.c++
    src/window/GLFW/glfw_window.c++
    src/window/SDL/sdl_window.c++
    src/common/camera/camera.c++
    src/common/ui/deui.c++
    src/common/material/material.c++
    xternal/glad/src/glad.c
    src/common/shader/shader.c++
    src/common/transform/transform.h
    src/common/particle/particle.h
    src/common/particle/particle.c++
    )

target_link_libraries(delib PUBLIC SDL3::SDL3)
target_link_libraries(delib PUBLIC glm)
target_link_libraries(delib PUBLIC glfw)

target_include_directories(delib PUBLIC
       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/xternal/SDL/include>
       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/xternal/glad/include>
       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/xternal/cgltf/include>
       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/xternal/stb>
       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/utility>
       $<INSTALL_INTERFACE:include>
   )

add_executable (delib_test
    test/main.c++
    test/test_app.c++
    test/test_scene.c++
    )

target_link_libraries (delib_test delib)
