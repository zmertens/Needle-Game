#include "ZepHandler.hpp"

#include <m3rdparty/animation/timer.h>
#include <zep/buffer.h>

ZepHandler::ZepHandler(const std::string &startupFilePath)
    : mEditor(new Zep::ZepEditor_ImGui(startupFilePath))
{
    mEditor->RegisterCallback(this);
}

bool ZepHandler::init()
{
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

    mEditor->InitWithText("Shader.vert", shader);

    return true;
}

void ZepHandler::cleanUp()
{
}

void ZepHandler::Notify(std::shared_ptr<Zep::ZepMessage> message)
{
 if (message->messageId == Zep::Msg::Tick)
        {
#ifndef __APPLE__
            // MUtils::Watcher::Instance().Update();
#endif
        }
        else if (message->messageId == Zep::Msg::Quit)
        {
            mQuit = true;
        }
        else if (message->messageId == Zep::Msg::ToolTip)
        {
            auto spTipMsg = std::static_pointer_cast<Zep::ToolTipMessage>(message);
            if (spTipMsg->location != -1l && spTipMsg->pBuffer)
            {
                auto pSyntax = spTipMsg->pBuffer->GetSyntax();
                if (pSyntax)
                {
                    if (pSyntax->GetSyntaxAt(spTipMsg->location) == Zep::ThemeColor::Identifier)
                    {
                        auto spMarker = std::make_shared<Zep::RangeMarker>();
                        spMarker->description = "This is an identifier";
                        spMarker->highlightColor = Zep::ThemeColor::Identifier;
                        spMarker->textColor = Zep::ThemeColor::Text;
                        spTipMsg->spMarker = spMarker;
                        spTipMsg->handled = true;
                    }
                    else if (pSyntax->GetSyntaxAt(spTipMsg->location) == Zep::ThemeColor::Keyword)
                    {
                        auto spMarker = std::make_shared<Zep::RangeMarker>();
                        spMarker->description = "This is a keyword";
                        spMarker->highlightColor = Zep::ThemeColor::Keyword;
                        spMarker->textColor = Zep::ThemeColor::Text;
                        spTipMsg->spMarker = spMarker;
                        spTipMsg->handled = true;
                    }
                }
            }
        }
}

Zep::ZepEditor& ZepHandler::GetEditor() const
{
    return *mEditor;
}

void ZepHandler::display(unsigned int width, unsigned int height)
{
    ImGui::Begin("Zep Stuff");
    // std::cout << "Zepp Stuff" << std::endl;
    ImGui::End();

    // Zep Window
    // if (ImGui::BeginMainMenuBar())
    // {
    //     if (ImGui::BeginMenu("Settings"))
    //     {
    //         if (ImGui::BeginMenu("Editor Mode"))
    //         {
    //             bool enabledVim = true;
    //             // bool enabledVim = strcmp(mZepHandler.getEditor()->GetCurrentMode()->Name(), Zep::ZepMode_Vim::StaticName()) == 0;
    //             bool enabledNormal = !enabledVim;
    //             if (ImGui::MenuItem("Vim", "CTRL+2", &enabledVim))
    //             {
    //                 mEditor->SetMode(Zep::ZepMode_Vim::StaticName());
    //             }
    //             else if (ImGui::MenuItem("Standard", "CTRL+1", &enabledNormal))
    //             {
    //                 mEditor->SetMode(Zep::ZepMode_Standard::StaticName());
    //             }
    //             ImGui::EndMenu();
    //         }

    //         if (ImGui::BeginMenu("Theme"))
    //         {
    //             bool enabledDark = mEditor->GetTheme().GetThemeType() == Zep::ThemeType::Dark ? true : false;
    //             bool enabledLight = !enabledDark;

    //             if (ImGui::MenuItem("Dark", "", &enabledDark))
    //             {
    //                 mEditor->GetTheme().SetThemeType(Zep::ThemeType::Dark);
    //             }
    //             else if (ImGui::MenuItem("Light", "", &enabledLight))
    //             {
    //                 mEditor->GetTheme().SetThemeType(Zep::ThemeType::Light);
    //             }
    //             ImGui::EndMenu();
    //         }
    //         ImGui::EndMenu();
    //     }

    //     if (ImGui::BeginMenu("Window"))
    //     {
    //         auto pTabWindow = mEditor->GetActiveTabWindow();
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

    //     ImGui::EndMainMenuBar();
    // }

    // This is a bit messy; and I have no idea why I don't need to remove the menu fixed_size from the calculation!

    // auto menuSize = ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetFontSize();
    // ImGui::SetNextWindowPos(ImVec2(0, menuSize));
    // ImGui::SetNextWindowSize(ImVec2(float(width), float(height))); // -menuSize)));

    // ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    // ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    // ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    // ImGui::Begin("Zep", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar /*| ImGuiWindowFlags_NoScrollbar*/);
    // ImGui::PopStyleVar(4);

    // // 'hide' the window contents from ImGui, so it doesn't try dragging when we move our scrollbar, etc.
    // ImGui::InvisibleButton("ZepContainer", ImGui::GetWindowSize());
    // ImGui::End();

    mEditor->SetDisplayRegion(Zep::toNVec2f(ImGui::GetWindowPos()), Zep::toNVec2f(ImGui::GetWindowSize()));
    mEditor->Display();
}

void ZepHandler::handleInput()
{
    mEditor->HandleInput();
}

void ZepHandler::setDisplayRegion(const Zep::NVec2f &pos, const Zep::NVec2f &size)
{
    mEditor->SetDisplayRegion(pos, size);
}
