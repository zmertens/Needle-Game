#include "GlfwHandler.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <cstdio>

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
: mWindowIconPath(GLFW_ICON_FILEPATH)
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    mGlfwWindow = glfwCreateWindow(GLFW_WINDOW_X, GLFW_WINDOW_Y, GLFW_WINDOW_TITLE, nullptr, nullptr);
    if (!mGlfwWindow)
    {
        glfwTerminate();
        return !success;
    }

    if (mWindowIconPath.compare("") != 0)
    {
        this->loadImages(mWindowIconPath);
        glfwSetWindowIcon(mGlfwWindow, 1, mGlfwIcon);
    }

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

bool GlfwHandler::loadImages(std::string filepath)
{
    int x, y, comps;
    unsigned char* imageData = stbi_load(filepath.c_str(), &x, &y, &comps, 1);

    mGlfwIcon->pixels = imageData;

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