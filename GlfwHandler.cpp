#include "GlfwHandler.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <cstdio>

#if defined(NEEDLE_DEBUG)
#include <iostream>
#endif // NEEDLE_DEBUG

/**
 * Static
 */
std::array<bool, 1024> GlfwHandler::mInputs = {false};

void GlfwHandler::setErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void GlfwHandler::setKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    using namespace std;
    if (key == GLFW_KEY_DELETE && action == GLFW_PRESS)
    {
        mInputs[key] = true;
    }
    else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        mInputs[key] = true;
    }
}

GlfwHandler::GlfwHandler()
: mTitle("GLFW Application")
, mWindowIconPath("")
{

}

GlfwHandler::GlfwHandler(const std::string& title, const std::string& iconpath)
: mTitle(title)
, mWindowIconPath(iconpath)
{

}

bool GlfwHandler::init()
{
    using namespace std;
    static constexpr bool success = true;

    if (!glfwInit())
    {
        return !success;
    }

    mGlslVersion = "";
#if defined(__APPLE__)
    mGlslVersion = "#version 150";
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    mGlslVersion = "#version 130";
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif // __APPLE__

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    mGlfwWindow = glfwCreateWindow(GLFW_WINDOW_X, GLFW_WINDOW_Y, mTitle.c_str(), nullptr, nullptr);
    if (!mGlfwWindow)
    {
        glfwTerminate();
        return !success;
    }

    if (mWindowIconPath.compare("") != 0)
    {
        int x, y, comps;
        unsigned char* imageData = stbi_load(mWindowIconPath.c_str(), &x, &y, &comps, 1);
        GLFWimage glfwIcon[1];
        glfwIcon->pixels = imageData;
        glfwSetWindowIcon(mGlfwWindow, 1, glfwIcon);
    }

#if defined(NEEDLE_DEBUG)
    cout << "Making Glfw current context" << endl;
#endif // NEEDLE_DEBUG

    glfwMakeContextCurrent(mGlfwWindow);
    // Enable Vsync
    glfwSwapInterval(V_SYNC_FLAG);

    glfwSetErrorCallback(setErrorCallback);
    glfwSetKeyCallback(mGlfwWindow, setKeyCallback);

    // Initialize Glad to use OpenGL after GLFW context creation
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        glfwTerminate();
        return !success;
    }

    return success;
}

void GlfwHandler::cleanUp()
{
    glfwDestroyWindow(mGlfwWindow);
    glfwTerminate();
}

/**
 * @TODO -- Plan is to utilize this and properly accept GFLWimage*
 */
bool GlfwHandler::loadImages(std::string filepath)
{
    int x, y, comps;
    unsigned char* imageData = stbi_load(filepath.c_str(), &x, &y, &comps, 1);

    return true;
}

void GlfwHandler::swapBuffers() const
{
    glfwSwapBuffers(mGlfwWindow);
}

std::string GlfwHandler::getGlString() const
{
    return mGlslVersion;
}

GLFWwindow* GlfwHandler::getGlfwWindow() const
{
    return mGlfwWindow;
}

std::array<bool, 1024> GlfwHandler::getKeys() const
{
    return mInputs;
}

void GlfwHandler::resetKeys()
{
    for (bool& keys : mInputs)
    {
        keys = false;
    }
}