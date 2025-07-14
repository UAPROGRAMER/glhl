#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glhl/window.hpp>
#include "internal/window.hpp"
#include <glhl/error_handling.hpp>

#include <iostream>

namespace glhl {

Window::Window(int width, int height, const char* title) {
    window_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window_ptr == nullptr)
        throw GLHLError(error::WINDOW_CREATION_FAIL, "Failed to create window.");

    glfwSetFramebufferSizeCallback(window_ptr, glfwWindowSizeChangeCallback);

    use();

    // load gl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw GLHLError(error::GL_LOADER_FAIL, "Failed to load glad gl loader.");

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
        glfwDestroyWindow(window_ptr);
}

GLFWwindow* Window::getPtr() const {
    if (window_ptr == nullptr)
        throw GLHLError(error::WINDOW_OPERATION_FAIL, "Failed to get ptr of the window.");
    return window_ptr;
}

void Window::getSize(int& width, int& height) const {
    if (window_ptr == nullptr)
        throw GLHLError(error::WINDOW_OPERATION_FAIL, "Failed to get size of the window.");
    int temp_x, temp_y;
    glfwGetWindowSize(window_ptr, &temp_x, &temp_y);
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

void Window::close() const {
    if (window_ptr == nullptr)
        throw GLHLError(error::WINDOW_OPERATION_FAIL, "Failed to close the window.");
    glfwWindowShouldClose(window_ptr);
}

void Window::forseClose() {
    if (window_ptr == nullptr)
        throw GLHLError(error::WINDOW_OPERATION_FAIL, "Failed to forse close the window.");
    glfwDestroyWindow(window_ptr);
}

void Window::use() const {
    if (window_ptr == nullptr)
        throw GLHLError(error::WINDOW_OPERATION_FAIL, "Failed to use the window.");
    glfwMakeContextCurrent(window_ptr);
}

void Window::flip() const {
    if (window_ptr == nullptr)
        throw GLHLError(error::WINDOW_OPERATION_FAIL, "Failed to flip the window.");
    glfwSwapBuffers(window_ptr);
}

bool Window::shouldClose() const {
    if (window_ptr == nullptr)
        return true;
    return glfwWindowShouldClose(window_ptr) == 1;
}

void glfwWindowSizeChangeCallback(GLFWwindow* window, int width, int height) {
    GLFWwindow* context_window = glfwGetCurrentContext();
    if (window == context_window) {
        glViewport(0, 0, width, height);
        return;
    }
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(context_window);
}

}