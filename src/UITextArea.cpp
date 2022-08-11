#include "UITextArea.hpp"
#include <iostream>
UITextArea::UITextArea(const std::string &font_path, int x,int y,std::string text,std::function<void(const std::string &)> callback):UIText(font_path,x,y,text),on_input(callback){
    SDL_StopTextInput();
}
void UITextArea::init(SDL_Renderer * renderer,EventManager & manager,UI &ui){
    UIText::init(renderer,manager,ui);
    
    auto size = getSize();
    SDL_Rect input_rect={x,y,size.first,size.second};
    SDL_SetTextInputRect(&input_rect);
    manager.addEventHandler(SDL_TEXTINPUT,{this,[](UIComponent *owner,const SDL_Event & ev){
        UITextArea * area = (UITextArea *)owner;
        area->setText(area->getText()+ev.text.text);
    }});

    manager.addEventHandler(SDL_KEYDOWN,{this,[](UIComponent *owner,const SDL_Event & ev){
        UITextArea * area = (UITextArea *)owner;
        if(!SDL_IsTextInputActive())
            return;
        if(ev.key.keysym.sym == SDLK_BACKSPACE){
            if(area->getText().size()> area->prompt_len)
                area->setText(area->getText().substr(0,area->getText().size()-1));
        }
        if(ev.key.keysym.sym == SDLK_ESCAPE){
            area->active = false;
            SDL_StopTextInput();
        }
        if(ev.key.keysym.sym == SDLK_RETURN){
            SDL_StopTextInput();
            area->active = false;
            area->on_input(area->getText().substr(area->prompt_len));
        }
    }});
}
void UITextArea::startInput(const std::string & prompt ){
    active = true;
    setText(prompt);
    SDL_StartTextInput();
    prompt_len = prompt.size();
}
bool UITextArea::isEnabled() const {
    return active;
}