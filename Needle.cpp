#include "Needle.hpp"

// Zep libraries
#include <zep/imgui/display_imgui.h>
#include <zep/imgui/editor_imgui.h>
#include <zep/mode_standard.h>
#include <zep/mode_vim.h>
#include <zep/theme.h>
#include <zep/tab_window.h>
#include <zep/window.h>

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

    // Zep variables and fields
    const std::string shader = R"R(
    #version 330 core

    uniform mat4 Projection;

    // Coordinates  of the geometry
    layout(location = 0) in vec3 in_position;
    layout(location = 1) in vec2 in_tex_coord;
    layout(location = 2) in vec4 in_color;

    // Outputs to the pixel shader
    out vec2 frag_tex_coord;
    out vec4 frag_color;

    void main()
    {
        gl_Position = Projection * vec4(in_position.xyz, 1.0);
        frag_tex_coord = in_tex_coord;
        frag_color = in_color;
    }
    )R";
    // A helper struct for Zep to init the editor and handle callbacks
//     struct ZepContainer : public IZepComponent
//     {
//         ZepContainer(const std::string& startupFilePath)
//             : spEditor(std::make_unique<ZepEditor_ImGui>(ZEP_ROOT))
//         {

//             // File watcher not used on apple yet ; needs investigating as to why it doesn't compile/run 
// #ifndef __APPLE__
// MUtils::Watcher::Instance().AddWatch(ZEP_ROOT, [&](const ZepPath & path)
// {
//     spEditor->OnFileChanged(path);
// }, false);
// #endif

//             spEditor->RegisterCallback(this);

//             float ddpi = 0.0f;
//             float hdpi = 0.0f;
//             float vdpi = 0.0f;
//             auto res = SDL_GetDisplayDPI(0, &ddpi, &hdpi, &vdpi);
//             if (res == 0 && hdpi != 0)
//             {
//                 spEditor->SetPixelScale(hdpi / 96.0f);
//             }

//             if (!startupFilePath.empty())
//             {
//                 spEditor->InitWithFileOrDir(startupFilePath);
//             }
//             else
//             {
//                 spEditor->InitWithText("Shader.vert", shader);
//             }
//         }

//         ZepContainer()
//         {
//             spEditor->UnRegisterCallback(this);
//         }

//         // Inherited via IZepComponent
//         virtual void Notify(std::shared_ptr<ZepMessage> message) override
//         {
//             if (message->messageId == Msg::Tick)
//             {
// #ifndef __APPLE__
// MUtils::Watcher::Instance().Update();
// #endif
//             }
//             else if (message->messageId == Msg::Quit)
//             {
//                 quit = true;
//             }
//             else if (message->messageId == Msg::ToolTip)
//             {
//                 auto spTipMsg = std::static_pointer_cast<ToolTipMessage>(message);
//                 if (spTipMsg->location != -1l && spTipMsg->pBuffer)
//                 {
//                     auto pSyntax = spTipMsg->pBuffer->GetSyntax();
//                     if (pSyntax)
//                     {
//                         if (pSyntax->GetSyntaxAt(spTipMsg->location) == ThemeColor::Identifier)
//                         {
//                             auto spMarker = std::make_shared<RangeMarker>();
//                             spMarker->description = "This is an identifier";
//                             spMarker->highlightColor = ThemeColor::Identifier;
//                             spMarker->textColor = ThemeColor::Text;
//                             spTipMsg->spMarker = spMarker;
//                             spTipMsg->handled = true;
//                         }
//                         else if (pSyntax->GetSyntaxAt(spTipMsg->location) == ThemeColor::Keyword)
//                         {
//                             auto spMarker = std::make_shared<RangeMarker>();
//                             spMarker->description = "This is a keyword";
//                             spMarker->highlightColor = ThemeColor::Keyword;
//                             spMarker->textColor = ThemeColor::Text;
//                             spTipMsg->spMarker = spMarker;
//                             spTipMsg->handled = true;
//                         }
//                     }
//                 }
//             }
//         }

//         virtual ZepEditor& GetEditor() const override
//         {
//             return *spEditor;
//         }

//         bool quit = false;
//         std::unique_ptr<ZepEditor_ImGui> spEditor;
//     };
//     ZepContainer zep ("");

    ImVec4 clearColor = ImVec4(0.35f, 0.55f, 0.71f, 1.0f);
#if defined(NEEDLE_DEBUG)
    cout << "Starting game loop" << endl;
#endif // NEEDLE_DEBUG
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
        // zep.spEditor->SetDisplayRegion(toNVec2f(ImGui::GetWindowPos()), toNVec2f(ImGui::GetWindowSize()));

        // // Display the editor inside this window
        // zep.spEditor->Display();
        // zep.spEditor->HandleInput();

        mGlTriangle->draw();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Double-Buffered, swap buffers
        mGlfwHandler.swapBuffers();
    }

    cout << "Application Cleanup" << endl;

    mGlTriangle->cleanUp();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    mGlfwHandler.cleanUp();

    return EXIT_SUCCESS;
}