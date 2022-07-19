#pragma once
#include "UI.hpp"
class UIImage:public UIComponent{
    SDL_Rect rect;
    SDL_Texture *texture;
    SDL_Surface *surface;
    public:
    UIImage(const char *file,int x,int y);
    virtual void init(SDL_Renderer * renderer)override;
    virtual SDL_Texture * render(SDL_Rect & rect,SDL_Renderer * renderer) const override;
    virtual ~UIImage();

};