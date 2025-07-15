#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glhl/window.hpp>
#include "internal/window.hpp"
#include <glhl/error_handling.hpp>
#include <glhl/keys.hpp>

namespace glhl {

Window::Window(int width, int height, const char* title) {
    window_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window_ptr == nullptr)
        throw GLHLError(error::WINDOW_CREATION_FAIL, "Failed to create window.");

    windowShouldCloseMap.insert({getPtr(), glfwWindowShouldClose(getPtr())});

    glfwSetFramebufferSizeCallback(getPtr(), glfwWindowSizeChangeCallback);

    use();

    glfwSwapInterval(1);

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

// Utility

GLFWwindow* Window::getPtr() const {
    if (window_ptr == nullptr)
        throw GLHLError(error::WINDOW_OPERATION_FAIL, "ERROR::glhl:Window::getPtr: window_ptr value is nullptr.");
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

//temp

bool Window::isShouldClose() const {
    return glfwWindowShouldClose(getPtr());
}

// Window

void Window::close() {
    glfwDestroyWindow(getPtr());
    windowShouldCloseMap.erase(getPtr());
    window_ptr = nullptr;
}

void Window::use() const {
    if (glfwGetCurrentContext() != getPtr())
        glfwMakeContextCurrent(getPtr());
}

void Window::flip() const {
    glfwSwapBuffers(getPtr());
}

void Window::setVSync(bool value) const {
    use();
    glfwSwapInterval(value ? 1 : 0);
}

// Input

bool Window::isKeyPressed(int key) const {
    return glfwGetKey(getPtr(), key) == GLFW_PRESS;
}

// Other

void glfwWindowSizeChangeCallback(GLFWwindow* window, int width, int height) {
    if (glfwGetCurrentContext() != window)
        glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
}

}