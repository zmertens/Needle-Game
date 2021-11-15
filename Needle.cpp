#include "Needle.hpp"

#include "ZepHandler.hpp"

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
    if (glInitSuccess)
    {
#if defined(NEEDLE_DEBUG)
        cout << "GL Objects Initialized Successfully" << endl;
#endif 
    }
    
    // mZepHandler.init();

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

        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // if (ImGui::BeginMainMenuBar())
        // {
        //     if (ImGui::BeginMenu("Settings"))
        //     {
        //         if (ImGui::BeginMenu("Editor Mode"))
        //         {
        //             bool enabledVim = strcmp(mZepHandler.getEditor()->GetCurrentMode()->Name(), Zep::ZepMode_Vim::StaticName()) == 0;
        //             bool enabledNormal = !enabledVim;
        //             if (ImGui::MenuItem("Vim", "CTRL+2", &enabledVim))
        //             {
        //                 mZepHandler.getEditor()->SetMode(Zep::ZepMode_Vim::StaticName());
        //             }
        //             else if (ImGui::MenuItem("Standard", "CTRL+1", &enabledNormal))
        //             {
        //                 mZepHandler.getEditor()->SetMode(Zep::ZepMode_Standard::StaticName());
        //             }
        //             ImGui::EndMenu();
        //         }

        //         if (ImGui::BeginMenu("Theme"))
        //         {
        //             bool enabledDark = mZepHandler.getEditor()->GetTheme().GetThemeType() == Zep::ThemeType::Dark ? true : false;
        //             bool enabledLight = !enabledDark;

        //             if (ImGui::MenuItem("Dark", "", &enabledDark))
        //             {
        //                 mZepHandler.getEditor()->GetTheme().SetThemeType(Zep::ThemeType::Dark);
        //             }
        //             else if (ImGui::MenuItem("Light", "", &enabledLight))
        //             {
        //                 mZepHandler.getEditor()->GetTheme().SetThemeType(Zep::ThemeType::Light);
        //             }
        //             ImGui::EndMenu();
        //         }
        //         ImGui::EndMenu();
        //     }

        //     if (ImGui::BeginMenu("Window"))
        //     {
        //         auto pTabWindow = mZepHandler.getEditor()->GetActiveTabWindow();
        //         if (ImGui::MenuItem("Horizontal Split"))
        //         {
        //             pTabWindow->AddWindow(&pTabWindow->GetActiveWindow()->GetBuffer(), pTabWindow->GetActiveWindow(), false);
        //         }
        //         else if (ImGui::MenuItem("Vertical Split"))
        //         {
        //             pTabWindow->AddWindow(&pTabWindow->GetActiveWindow()->GetBuffer(), pTabWindow->GetActiveWindow(), true);
        //         }
        //         ImGui::EndMenu();
        //     }

            // Helpful for diagnostics
            // Make sure you run a release build; iterator debugging makes the debug build much slower
            // Currently on a typical file, editor display time is < 1ms, and editor editor time is < 2ms
            // if (ImGui::BeginMenu("Timings"))
            // {
            //     for (auto& p : globalProfiler.timerData)
            //     { 
            //         std::ostringstream strval;
            //         strval << p.first << " : " << p.second.current / 1000.0 << "ms";// << " Last: " << p.second.current / 1000.0 << "ms";
            //         ImGui::MenuItem(strval.str().c_str());
            //     }
            //     ImGui::EndMenu();
            // }

            // ImGui::EndMainMenuBar();
        // }


        // This is a bit messy; and I have no idea why I don't need to remove the menu fixed_size from the calculation!
        int w, h, displayMode;
        glfwGetFramebufferSize(mGlfwHandler.getGlfwWindow(), &w, &h);
        auto menuSize = ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetFontSize();
        ImGui::SetNextWindowPos(ImVec2(0, menuSize));
        ImGui::SetNextWindowSize(ImVec2(float(w), float(h))); // -menuSize)));

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
        ImGui::Begin("Zep", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar /*| ImGuiWindowFlags_NoScrollbar*/);
        ImGui::PopStyleVar(4);

        // 'hide' the window contents from ImGui, so it doesn't try dragging when we move our scrollbar, etc.
        ImGui::InvisibleButton("ZepContainer", ImGui::GetWindowSize());

        // // TODO: Change only when necessray
        // mZepHandler.setDisplayRegion(Zep::toNVec2f(ImGui::GetWindowPos()), Zep::toNVec2f(ImGui::GetWindowSize()));

        // // Display the editor inside this window
        // mZepHandler.display();
        // mZepHandler.handleInput();

        mGlTriangle->draw();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Double-Buffered, swap buffers
        mGlfwHandler.swapBuffers();
    }

    cout << "Application Cleanup" << endl;

    mGlTriangle->cleanUp();
    // mZepHandler.cleanUp();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    mGlfwHandler.cleanUp();

    return EXIT_SUCCESS;
}