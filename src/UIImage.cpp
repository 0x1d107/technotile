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

void UIImage::init(SDL_Renderer * renderer,EventManager & manager,UI& ui){
    texture=SDL_CreateTextureFromSurface(renderer,surface);
    if(!texture)throw std::runtime_error(SDL_GetError());
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