#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glhl/basic.hpp>
#include <glhl/error_handling.hpp>
#include "internal/error_handling.hpp"
#include "internal/window.hpp"

namespace glhl {

void init() {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
        throw GLHLError(Errors::INIT_FAIL, "Failed to initialize GLFW.");

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
    for (const auto& pair : windowEventsMap) {
        const auto key = pair.first;
        auto& events = windowEventsMap.at(key);
        events.clear();
        if (glfwWindowShouldClose(key))
            events.push_back(Event(EventTypes::QUIT));

        for (const auto& key_event : windowKeyEventsMap.at(key))
            events.push_back(key_event);
        windowKeyEventsMap.at(key).clear();
    }
}

}