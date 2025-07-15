#ifndef GLHL_INTERNAL_WINDOW_HPP
#define GLHL_INTERNAL_WINDOW_HPP

#include <GLFW/glfw3.h>

#include <unordered_map>

namespace glhl {

static std::unordered_map<GLFWwindow*, bool> windowShouldCloseMap;

void glfwWindowSizeChangeCallback(GLFWwindow* window, int width, int height);

}

#endif