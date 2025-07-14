cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(glhl_library)

# GLAD LIB
set(glad_sources 
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/glad.c
)
add_library(glad OBJECT ${glad_sources})
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

# GLHL LIB
file(GLOB source CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_library(glhl STATIC
    ${source}
    $<TARGET_OBJECTS:glad>
)
target_include_directories(glhl BEFORE PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

# LINKING

if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(glhl PUBLIC glfw OpenGL::GL)

# INSTALATION
install(TARGETS glhl DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)