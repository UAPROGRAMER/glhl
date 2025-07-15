#ifndef GLHL_HPP
#define GLHL_HPP

#define GLHL_VERSION_MAJOR 0
#define GLHL_VERSION_MINOR 0
#define GLHL_VERSION_PATCH 1

#define GLHL_VERSION_STRING "0.0.1"

namespace glhl {

static constexpr int VERSION_MAJOR = GLHL_VERSION_MAJOR;
static constexpr int VERSION_MINOR = GLHL_VERSION_MINOR;
static constexpr int VERSION_PATCH = GLHL_VERSION_PATCH;

static constexpr const char* VERSION_STRING = GLHL_VERSION_STRING;

}

#include "glhl/basic.hpp"
#include "glhl/error_handling.hpp"
#include "glhl/keys.hpp"
#include "glhl/window.hpp"

#endif