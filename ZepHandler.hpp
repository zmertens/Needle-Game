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
class ZepHandler : public IHandler, Zep::IZepComponent
{
public:
    explicit ZepHandler(const std::string &startupFilePath);

    virtual bool init() override;
    virtual void cleanUp() override;

    virtual void Notify(std::shared_ptr<Zep::ZepMessage> message) override;
    virtual Zep::ZepEditor& GetEditor() const override;

    void display(unsigned int width, unsigned int height);
    void handleInput();
    void setDisplayRegion(const Zep::NVec2f& pos, const Zep::NVec2f& size);

private:
    std::unique_ptr<Zep::ZepEditor_ImGui> mEditor;
};

#endif // ZEPHANDLER_HPP