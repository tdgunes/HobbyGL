cmake_minimum_required(VERSION 3.3)
project(HobbyGL)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(Lua REQUIRED)


if (!GLEW_FOUND)
    message(FATAL_ERROR "GLEW not found")
endif ()


include_directories(
        "include/"
        ${SDL2_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${LUA_INCLUDE_DIRS}
)

set(SOURCE_FILES
        src/main.cpp
        src/Shaders.cpp
        include/Shaders.h
        src/Utils.cpp
        include/Utils.h
        src/Sprite.cpp
        include/Sprite.h
        src/Renderer.cpp
        include/Renderer.h
        include/Constants.h
        src/Controls.cpp
        include/Controls.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARY}
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${GLM_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${LUA_LIBRARIES}
        )


