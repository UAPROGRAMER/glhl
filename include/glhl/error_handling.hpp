#ifndef GLHL_ERROR_HANDLING_HPP
#define GLHL_ERROR_HANDLING_HPP

#include <exception>
#include <string>

namespace glhl {

namespace Errors {

enum {
    UNKNOWN_ERROR = 0x01,
    INIT_FAIL,
    GL_LOADER_FAIL,
    WINDOW_CREATION_FAIL,
    WINDOW_OPERATION_FAIL,
};

}

class GLHLError : public std::exception {
public:
    const int code;
    const std::string desc;

    GLHLError(int code, std::string desc);
    GLHLError(int code, const char* desc);

    const char* what() const noexcept override;
};

}

#endif