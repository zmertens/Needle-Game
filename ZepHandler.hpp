#ifndef ZEPHANDLER_HPP
#define ZEPHANDLER_HPP

// Zep libraries

#include "../zep/zep/imgui/display_imgui.h"
#include "../zep/zep/imgui/editor_imgui.h"
#include "../zep/zep/mode_standard.h"
#include "../zep/zep/mode_vim.h"
#include "../zep/zep/theme.h"
#include "../zep/zep/tab_window.h"
#include "../zep/zep/window.h"
#include "../zep/zep/buffer.h"

#include "IHandler.hpp"

#include <memory>

// A helper struct for Zep to init the editor and handle callbacks
class ZepHandler : public IHandler
{
public:
    explicit ZepHandler(const std::string &startupFilePath);

    virtual bool init() override;
    virtual void cleanUp() override;

    void notify();
    void display();
    void handleInput();
    void setDisplayRegion(const Zep::NVec2f& pos, const Zep::NVec2f& size);
    const std::unique_ptr<Zep::ZepEditor_ImGui>& getEditor() const;

private:
    std::unique_ptr<Zep::ZepBuffer> mBuffer;
    std::unique_ptr<Zep::ZepEditor_ImGui> mEditor;
};

#endif // ZEPHANDLER_HPP