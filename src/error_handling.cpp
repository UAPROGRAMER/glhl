#include <glhl/error_handling.hpp>
#include "internal/error_handling.hpp"

namespace glhl {

GLHLError::GLHLError(int code, std::string desc)
: code(code), desc(std::move(desc)) {}

GLHLError::GLHLError(int code, const char* desc)
: GLHLError(code, std::string(desc)) {}

const char* GLHLError::what() const noexcept {
    return desc.c_str();
}

void glfwErrorCallback(int code, const char* desc) {
    throw GLHLError(code, desc);
}

}