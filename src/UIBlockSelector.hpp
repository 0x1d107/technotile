#pragma once
#include "UI.hpp"
#include "UIGrid.hpp"
#include "UITextArea.hpp"
#include "World.hpp"
class UIBlockSelector:public UIComponent{
    World *world = NULL;
    UIGrid * grid = NULL;
    UITextArea * area = NULL;
    UIText * output = NULL;
    int x;
    int y;
    int sel =0;
    public:
    int getSelection();
    UIGrid * getGrid();
    UIBlockSelector(int x,int y,World & world,UIGrid * grid);
    void init(SDL_Renderer *renderer,EventManager & manager,UI& ui) override;
    SDL_Texture *render(SDL_Rect &rect,SDL_Renderer * renderer) const override;
    void select(int id);
};
