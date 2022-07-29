#include "UI.hpp"
#include <exception>
#include <stdexcept>

UI::UI(){
    if(SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error(SDL_GetError());
    if(SDL_CreateWindowAndRenderer(800,600,0,&window,&renderer))
        throw std::runtime_error(SDL_GetError());

}
void UI::addComponent(UIComponent *comp){
    comp->init(renderer,event_manager);
    components.push_back(comp);
}
EventManager & UI::getManager(){
    return event_manager;
}
void UI::render(){
    if(SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE))
        throw std::runtime_error(SDL_GetError());
    if(SDL_RenderClear(renderer))
        throw std::runtime_error(SDL_GetError());
    for(auto c:components){
        if(!c->isEnabled())
            continue;
        SDL_Rect rect;
        SDL_Texture * tex = c->render(rect,renderer);
        if(!tex)
            continue;
        if(SDL_RenderCopy(renderer,tex,NULL,&rect))
            throw std::runtime_error(SDL_GetError());
    }
    SDL_RenderPresent(renderer);
}
void UI::runEventLoop(){
    while(1){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                return;
            }
            event_manager.handleEvent(event);
        }
        render();
    }
}
UI::~UI(){
    for(auto c:components){
        delete c;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void UI::getWindowSize(int &width,int  &height){
    SDL_GetWindowSize(window,&width,&height);
}

void EventManager::addEventHandler(SDL_EventType type, EventHandler handler){
    events[type].push_back(handler);
}

void EventManager::handleEvent(const SDL_Event &event){
    for(const auto & handler : events[(SDL_EventType)event.type]){
        if(!handler.owner->isEnabled())
            continue;
        handler.handler(handler.owner,event);
    }
}
