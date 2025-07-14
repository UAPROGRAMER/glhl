#ifndef GLHL_WINDOW_HPP
#define GLHL_WINDOW_HPP

#include <GLFW/glfw3.h>

namespace glhl {

class Window {
private:
    GLFWwindow* window_ptr;

    Window(const Window&) = delete;
    Window & operator=(const Window&) = delete;
public:
    Window(int width, int height, const char* title);
    ~Window();

    GLFWwindow* getPtr() const;

    void getSize(int& width, int& height) const;

    int getWidth() const;

    int getHeight() const;

    void close() const;

    void forseClose();

    void use() const;

    void flip() const;

    bool shouldClose() const;
};

}

#endif