#pragma once
#include "UI.hpp"
#include "World.hpp"
class UIGrid:public UIComponent{

    World *world=NULL;
    SDL_Renderer *renderer= NULL;
    public:
    int x=0;
    int y=0;
    UIGrid(World & world);
    World &getWorld();
    virtual void init(SDL_Renderer *renderer, EventManager &manager);
    virtual SDL_Texture * render(SDL_Rect & rect,SDL_Renderer * renderer)  const override;
    virtual ~UIGrid(){}



};