#pragma once
#include "UI.hpp"
#include "UIText.hpp"
#include <functional>
class UITextArea: public UIText{
    protected:
    std::function<void(const std::string &)> on_input=[](const std::string & s){};
    bool active = false;
    int prompt_len = 0;
    public:
    UITextArea(const std::string &font_path, int x,int y,std::string text, std::function<void(const std::string &)> callback);
    void startInput(const std::string & prompt);
    void init(SDL_Renderer * renderer,EventManager & manager,UI& ui)override;
    bool isEnabled() const override;
};