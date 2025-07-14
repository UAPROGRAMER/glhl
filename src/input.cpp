#include <glhl/input.hpp>
#include <glhl/error_handling.hpp>

namespace glhl {

Input::Input(const Window& window)
: window(window) {
    window.getPtr();
}

bool Input::isKeyPressed(int key) {
    return glfwGetKey(window.getPtr(), key) == GLFW_PRESS;
}

}