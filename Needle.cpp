#include "Needle.hpp"

Needle::Needle(int argc, char** argv)
: mGlfwHandler("Needle", "./assets/window_icon.png")
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
        cout << "TERMINATING GLFW APPLICATION\r\n" << "GLFW or GLAD failed to init" << endl;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplOpenGL3_Init(mGlfwHandler.getGlString().c_str());
    ImGui_ImplGlfw_InitForOpenGL(mGlfwHandler.getGlfwWindow(), true);

    ImVec4 clearColor = ImVec4(0.35f, 0.55f, 0.71f, 1.0f);
#if defined(NEEDLE_DEBUG)
    cout << "CHECKING BEFORE GAME LOOP" << endl;
#endif // NEEDLE_DEBUG
    while (!glfwWindowShouldClose(mGlfwHandler.getGlfwWindow()))
    {
        glfwPollEvents();

        auto keys = mGlfwHandler.getKeys();
        if (keys[GLFW_KEY_DELETE])
        {
#if defined(NEEDLE_DEBUG)
            cout << "VALIDATING GAME STATE" << endl;
#endif // NEEDLE_DEBUG
        }
        else if (keys[GLFW_KEY_ESCAPE])
        {
            break;
        }

        mGlfwHandler.resetKeys();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show_demo_window = true;
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Begin("Stuff");

#if defined(NEEDLE_DEBUG)
        static unsigned int timer = 0;
        if (timer >= 60)
        {
            cout << "Application average %.3f ms/frame (%.1f FPS): " <<
                (1000.0f / ImGui::GetIO().Framerate) << " " << ImGui::GetIO().Framerate << endl;
            timer = 0;
        }
        
        timer += 1;
#endif // NEEDLE_DEBUG
        
        ImGui::End();

        ImGui::Render();

        int displayWidth, displayHeight;
        glfwGetFramebufferSize(mGlfwHandler.getGlfwWindow(), &displayWidth, &displayHeight);
        glViewport(0, 0, displayWidth, displayHeight);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Double-Buffered, swap buffers
        mGlfwHandler.swapBuffers();
    }

    cout << "Application Cleanup" << endl;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    mGlfwHandler.cleanUp();

    return EXIT_SUCCESS;
}