#ifndef GLHL_INPUT_HPP
#define GLHL_INPUT_HPP

#include "keys.hpp"
#include "window.hpp"

namespace glhl {

class Input {
private:
    const Window& window;
public:
    Input(const Window& window);

    bool isKeyPressed(int key);
};

}

#endif