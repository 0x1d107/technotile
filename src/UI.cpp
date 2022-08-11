#include "UI.hpp"
#include <exception>
#include <stdexcept>
#include <utility>
#include <SDL2/SDL_ttf.h>
#include "UIText.hpp"

UI::UI(){
    if(SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error(SDL_GetError());
    if(SDL_CreateWindowAndRenderer(800,600,0,&window,&renderer))
        throw std::runtime_error(SDL_GetError());

}
void UI::addComponent(UIComponent *comp){
    comp->init(renderer,event_manager,*this);
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
Uint32 update_cbk(Uint32 interval,void *){
    
    SDL_Event update_event;
    update_event.type = SDL_USEREVENT;
    update_event.user.type = SDL_USEREVENT;
    update_event.user.code = 0;
    SDL_PushEvent(&update_event);


    return interval;
}
void UI::runEventLoop(){
    auto fpsometer = new UIText("ttf/pixel.ttf",0,0,"FPS: 0");
    addComponent(fpsometer);
    updateTimerId = SDL_AddTimer(100,update_cbk,NULL);
    const Uint32 cap = 34;// milliseconds
    while(1){
        Uint64 start = SDL_GetPerformanceCounter();
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                return;
            }
            event_manager.handleEvent(event);
        }
        render();
        Uint64 end = SDL_GetPerformanceCounter();
        Uint64 t = 1000*(end-start)/SDL_GetPerformanceFrequency();
        if(start!=end)fpsometer->setText("FPS: "+std::to_string(std::min(SDL_GetPerformanceFrequency()/(end-start),1000ul/cap)));
        if(cap>t)SDL_Delay(cap-t);
    }
}
UI::~UI(){
    for(auto c:components){
        delete c;
    }
    SDL_RemoveTimer(updateTimerId);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void UI::getWindowSize(int &width,int  &height){
    SDL_GetWindowSize(window,&width,&height);
}

void EventManager::addEventHandler(SDL_EventType type, EventHandler handler){
    events[type].push_front(handler);
}

void EventManager::handleEvent(const SDL_Event &event){
    for(const auto & handler : events[(SDL_EventType)event.type]){
        if(handler.owner && !handler.owner->isEnabled())
            continue;
        handler.handler(handler.owner,event);
    }
}
