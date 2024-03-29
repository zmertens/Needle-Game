#ifndef NEEDLE_HPP
#define NEEDLE_HPP

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstdio>
#include <array>
#include <memory>

#include "GlfwHandler.hpp"
#include "GlTriangle.hpp"
#include "ZepHandler.hpp"
#include "FileHandler.hpp"

class Needle
{
public:
    explicit Needle(int argc, char** argv);
    int doStuff();

private:
    GlfwHandler mGlfwHandler;

    std::unique_ptr<GlTriangle> mGlTriangle;
    ZepHandler mZepHandler;
    FileHandler mFileHandler;
    std::string mHaystack;

    int generateHaystack();
    static void setFramebufferCallback(GLFWwindow* window, int width, int height);
};

#endif // NEEDLE_HPP