#pragma once
#include <deque>
#include <unordered_map>
#include <functional>
#include <SDL2/SDL.h>


class UIComponent;
struct EventHandler{
    UIComponent *owner=NULL;
    void (*handler)(UIComponent *owner, const SDL_Event &ev) = NULL;
};

class EventManager{
    std::unordered_map<SDL_EventType,std::deque<EventHandler> > events;
    public:
    void addEventHandler(SDL_EventType type ,EventHandler handler);
    void handleEvent(const SDL_Event & event);

};
class UI;
class UIComponent{
    public:
    virtual void init(SDL_Renderer *renderer,EventManager & manager,UI& ui){};
    virtual SDL_Texture *render(SDL_Rect &rect,SDL_Renderer * renderer) const = 0;
    virtual bool isEnabled() const{
        return true;
    }
    virtual ~UIComponent(){};
};
class UI{
    SDL_Window *window=NULL;
    SDL_Renderer *renderer=NULL;
    std::deque<const UIComponent *> components;
    EventManager event_manager;
    SDL_TimerID updateTimerId=-1;
    public:
    UI();
    void getWindowSize(int& width,int& height);
    EventManager &getManager();
    void render();
    void addComponent(UIComponent *component);
    void runEventLoop();
    virtual ~UI();

};
