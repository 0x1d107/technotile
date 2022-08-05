#pragma once 
#include <string>
#include "UI.hpp"
#include <SDL2/SDL_ttf.h>

class UIText:public UIComponent{
    TTF_Font *font=NULL;
    SDL_Surface *surface=NULL;
    SDL_Texture *texture=NULL;
    int x;
    int y;
    SDL_Color color;
    SDL_Renderer *renderer=NULL;
    std::string text;
    public:
    UIText(const std::string &font_path, int x,int y,std::string text,SDL_Color color= {0xff,0xff,0xff,0});
    virtual void init(SDL_Renderer * renderer,EventManager & manager)override;
    const std::string & getText() const;
    void setText(const std::string &str);
    virtual SDL_Texture * render(SDL_Rect & rect,SDL_Renderer * renderer) const override;
    virtual ~UIText();
};
