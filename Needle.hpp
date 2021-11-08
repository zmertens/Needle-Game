#ifndef NEEDLE_HPP
#define NEEDLE_HPP

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstdio>
#include <array>

#include "GlfwHandler.hpp"
#include "ImguiHandler.hpp"

class Needle
{
public:
    explicit Needle(int argc, char** argv);
    int doStuff();

private:

    GlfwHandler mGlfwHandler;
};

#endif // NEEDLE_HPP