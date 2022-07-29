#include "UIImage.hpp"
#include <SDL2/SDL_image.h>
#include <stdexcept>
UIImage::UIImage(const char *file,int x,int y){
    rect.x = x;
    rect.y = y;
    surface = IMG_Load(file);
    if(!surface)throw std::runtime_error(SDL_GetError());
    rect.w= surface->w;
    rect.h= surface->h;

    texture = NULL;
}
static UIImage * DRAG = NULL;
void UIImage::init(SDL_Renderer * renderer,EventManager & manager){
    texture=SDL_CreateTextureFromSurface(renderer,surface);
    if(!texture)throw std::runtime_error(SDL_GetError());
    manager.addEventHandler(SDL_MOUSEBUTTONDOWN,{this,[](UIComponent *owner,const SDL_Event&event){
        UIImage* image = (UIImage *)owner;
        SDL_Rect rect = image->getRect();
        if(event.button.x>=rect.x&&event.button.x<=rect.x+rect.w&&event.button.y>=rect.y&&event.button.y<=rect.y+rect.h){
            DRAG = image;
            DRAG->setPosition(event.motion.x-rect.w/2,event.motion.y-rect.h/2);
        }

    }});

    manager.addEventHandler(SDL_MOUSEMOTION,{this,[](UIComponent *owner, const SDL_Event &event){
        if(DRAG){
            SDL_Rect rect = DRAG->getRect();
            DRAG->setPosition(event.motion.x-rect.w/2,event.motion.y-rect.h/2);
        }
    }});

    manager.addEventHandler(SDL_MOUSEBUTTONUP,{this,[](UIComponent *owner,const SDL_Event&event){
        DRAG = NULL;
    }});
}
void UIImage::setPosition(int x, int y){
    this->rect.x = x;
    this->rect.y = y;
}
SDL_Rect UIImage::getRect(){
    return rect;
}
SDL_Texture *UIImage::render(SDL_Rect &dst_rect,SDL_Renderer *renderer)const{
    dst_rect = rect;
    if(!texture)throw std::runtime_error(SDL_GetError());
    return texture;
}
UIImage::~UIImage(){
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}