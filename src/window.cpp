#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glhl/window.hpp>
#include "internal/window.hpp"
#include <glhl/error_handling.hpp>
#include <glhl/keys.hpp>

#include <iostream>

namespace glhl {

std::unordered_map<GLFWwindow*, std::vector<Event>> windowEventsMap;

std::unordered_map<GLFWwindow*, std::vector<Event>> windowKeyEventsMap;

Window::Window(int width, int height, const char* title) {
    window_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window_ptr == nullptr)
        throw GLHLError(Errors::WINDOW_CREATION_FAIL, "Failed to create window.");

    windowEventsMap.insert({getPtr(), {}});
    windowKeyEventsMap.insert({getPtr(), {}});

    glfwSetFramebufferSizeCallback(getPtr(), glfwWindowSizeChangeCallback);
    glfwSetKeyCallback(getPtr(), glfwWindowKeyCallback);

    use();

    glfwSwapInterval(1);

    // load gl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw GLHLError(Errors::GL_LOADER_FAIL, "Failed to load glad gl loader.");

    // enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable depth
    glEnable(GL_DEPTH_TEST);

    // enable one face drawing
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

Window::~Window() {
    if (window_ptr != nullptr)
        close();
}

// Utility

GLFWwindow* Window::getPtr() const {
    if (window_ptr == nullptr)
        throw GLHLError(Errors::WINDOW_OPERATION_FAIL, "ERROR::glhl:Window::getPtr: window_ptr value is nullptr.");
    return window_ptr;
}

void Window::getSize(int& width, int& height) const {
    int temp_x, temp_y;
    glfwGetWindowSize(getPtr(), &temp_x, &temp_y);
    width = temp_x;
    height = temp_y;
}

int Window::getWidth() const {
    int width, _;
    getSize(width, _);
    return width;
}

int Window::getHeight() const {
    int _, height;
    getSize(_, height);
    return height;
}

// Window

void Window::close() {
    glfwDestroyWindow(getPtr());
    windowEventsMap.erase(getPtr());
    windowKeyEventsMap.erase(getPtr());
    window_ptr = nullptr;
}

void Window::use() const {
    if (glfwGetCurrentContext() != getPtr())
        glfwMakeContextCurrent(getPtr());
}

void Window::setVSync(bool value) const {
    use();
    glfwSwapInterval(value ? 1 : 0);
}

// Input

bool Window::isKeyPressed(int key) const {
    return glfwGetKey(getPtr(), key) == GLFW_PRESS;
}

const std::vector<Event>& Window::getEvents() const {
    return windowEventsMap.at(getPtr());
}

// Graphycs

void Window::flip() const {
    glfwSwapBuffers(getPtr());
}

// Other

void glfwWindowSizeChangeCallback(GLFWwindow* window, int width, int height) {
    if (glfwGetCurrentContext() != window)
        glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
}

void glfwWindowKeyCallback(GLFWwindow* window, int key, int scan, int action, int mods) {
    auto& events = windowKeyEventsMap.at(window);
    if (action == GLFW_PRESS)
        events.push_back(Event(EventTypes::KEY_PRESSED, key));
    else if (action == GLFW_RELEASE)
        events.push_back(Event(EventTypes::KEY_RELEASED, key));
    else
        events.push_back(Event(EventTypes::KEY_REPEAT, key));
}

}