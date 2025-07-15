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

    // Utility

    GLFWwindow* getPtr() const;

    void getSize(int& width, int& height) const;

    int getWidth() const;

    int getHeight() const;

    bool isShouldClose() const; // temp

    // Window

    void close();

    void use() const;

    void flip() const;

    void setVSync(bool value) const;

    // Input

    bool isKeyPressed(int key) const;
};

}

#endif