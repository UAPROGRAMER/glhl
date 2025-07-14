#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glhl/basic.hpp>
#include <glhl/error_handling.hpp>
#include "internal/error_handling.hpp"

namespace glhl {

void init() {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
        throw GLHLError(error::INIT_FAIL, "Failed to initialize GLFW.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void quit() {
    glfwTerminate();
}

void poolEvents() {
    glfwPollEvents();
}

}