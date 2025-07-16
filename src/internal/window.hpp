#ifndef GLHL_INTERNAL_WINDOW_HPP
#define GLHL_INTERNAL_WINDOW_HPP

#include <GLFW/glfw3.h>

#include "glhl/event.hpp"

#include <unordered_map>
#include <vector>

namespace glhl {

extern std::unordered_map<GLFWwindow*, std::vector<Event>> windowEventsMap;

extern std::unordered_map<GLFWwindow*, std::vector<Event>> windowKeyEventsMap;

void glfwWindowSizeChangeCallback(GLFWwindow* window, int width, int height);

void glfwWindowKeyCallback(GLFWwindow* window, int key, int scan, int action, int mods);

}

#endif