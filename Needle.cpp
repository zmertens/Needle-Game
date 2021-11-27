#include "Needle.hpp"

#include <iostream>

/**
 * Statics
 */
void Needle::setFramebufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Needle::Needle(int argc, char** argv)
: mGlfwHandler("Needle", "./assets/window_icon.png")
, mGlTriangle(new GlTriangle())
, mZepHandler("")
, mFileHandler()
, mHaystack("My haystack")
{

}

int Needle::doStuff()
{
    using namespace std;

#ifdef NEEDLE_DEBUG
    cout << "Application DEBUG mode" << endl;
#endif

    if (!mGlfwHandler.init())
    {
        cerr << "TERMINATING GLFW APPLICATION\r\n" << "GLFW or GLAD failed to init" << endl;
        return EXIT_FAILURE;
    }

    glfwSetFramebufferSizeCallback(mGlfwHandler.getGlfwWindow(), setFramebufferCallback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplOpenGL3_Init(mGlfwHandler.getGlString().c_str());
    ImGui_ImplGlfw_InitForOpenGL(mGlfwHandler.getGlfwWindow(), true);

    bool glInitSuccess = mGlTriangle->init();
    if (!glInitSuccess)
    {
        cerr << "GL Objects failed to initialize" << endl;
    }
    
    if (!mZepHandler.init())
    {
        cerr << "Zep Handler did not init" << endl;
    }

    if (!mFileHandler.init())
    {
        cerr << "Filehandler did not init" << endl;
    }

    string fileContents = mFileHandler.readFile("./assets/heiroglyphics.md.txt");

#if defined(NEEDLE_DEBUG)
        cout << "File contents:\r\n" << fileContents << endl;
#endif // NEEDLE_DEBUG

    mHaystack.append(fileContents);

    ImVec4 clearColor = ImVec4(0.35f, 0.55f, 0.71f, 1.0f);
    while (!glfwWindowShouldClose(mGlfwHandler.getGlfwWindow()))
    {
        glfwPollEvents();

        auto keys = mGlfwHandler.getKeys();
        if (keys[GLFW_KEY_DELETE])
        {
#if defined(NEEDLE_DEBUG)
            cout << "DELETING A BUG" << endl;
#endif // NEEDLE_DEBUG
        }
        else if (keys[GLFW_KEY_ESCAPE])
        {
            // break;
        }

        mGlfwHandler.resetKeys();

        static constexpr unsigned int HAYSTACK_CUTOFF = 10;
        auto bufferStr = mZepHandler.getTextFromActiveBuffer();
        auto& activeBuffer = mZepHandler.GetEditor().GetActiveTabWindow()->GetActiveWindow()->GetBuffer();
        if (mHaystack.length() < HAYSTACK_CUTOFF)
        {
#if defined(NEEDLE_DEBUG)
            cout << "Generating a new haystack" << endl;
#endif // NEEDLE_DEBUG
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show_demo_window = false;
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        static unsigned int timer = 0;
        if (timer >= 60)
        {
#if defined(NEEDLE_DEBUG)
            cout << "Application average %.3f ms/frame (%.1f FPS): " <<
                (1000.0f / ImGui::GetIO().Framerate) << " " << ImGui::GetIO().Framerate << endl;
            // cout << "Haystack: " << mHaystack << endl;
#endif // NEEDLE_DEBUG
            timer = 0;
        }
        
        timer += 1;

        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Save battery by skipping display if not required.
        // This will check for cursor flash, for example, to keep that updated.
        if (!mZepHandler.GetEditor().RefreshRequired())
        {
            // continue;
        }

        // Display the editor inside this window
        int w, h, displayMode;
        glfwGetFramebufferSize(mGlfwHandler.getGlfwWindow(), &w, &h);
        // Display and handle input must go together
        mZepHandler.display(w, h); mZepHandler.handleInput();

        mGlTriangle->draw();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Double-Buffered, swap buffers
        mGlfwHandler.swapBuffers();
    }

    cout << "Application Cleanup" << endl;

    mGlTriangle->cleanUp();
    mZepHandler.cleanUp();
    mFileHandler.cleanUp();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    mGlfwHandler.cleanUp();

    return EXIT_SUCCESS;
}