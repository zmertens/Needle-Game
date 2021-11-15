#include "ZepHandler.hpp"

#include <m3rdparty/animation/timer.h>
#include <zep/buffer.h>

ZepHandler::ZepHandler(const std::string &startupFilePath)
: mBuffer()
// , mEditor(new Zep::ZepEditor_ImGui(""))
{
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

    // mEditor->RegisterCallback(this);
    // mEditor->InitWithText("Shader.vert", shader);
}

void ZepHandler::cleanUp()
{

}

void ZepHandler::notify()
{

}

void ZepHandler::display()
{
    // mEditor->Display();
}

void ZepHandler::handleInput()
{
    // mEditor->HandleInput();
}

void ZepHandler::setDisplayRegion(const Zep::NVec2f& pos, const Zep::NVec2f& size)
{
    // mEditor->SetDisplayRegion(pos, size);
}

const std::unique_ptr<Zep::ZepEditor_ImGui>& ZepHandler::getEditor() const
{
    return mEditor;
}