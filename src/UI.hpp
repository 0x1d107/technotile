#pragma once
#include <deque>
#include <SDL2/SDL.h>
class UIComponent{
    public:
    virtual void init(SDL_Renderer *renderer){};
    virtual SDL_Texture *render(SDL_Rect &rect,SDL_Renderer * renderer) const = 0;
    virtual ~UIComponent(){};
};

class UI{
    SDL_Window *window=NULL;
    SDL_Renderer *renderer=NULL;
    std::deque<const UIComponent *> components;
    public:
    UI();
    void render();
    void addComponent(UIComponent *component);
    void runEventLoop();
    virtual ~UI();

};
