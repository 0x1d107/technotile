#include "UIText.hpp"
#include <stdexcept>
#include <iostream>
UIText::UIText(const std::string &font_path, int x,int y,std::string text,SDL_Color color ,int size){
    if(TTF_Init())
        throw std::runtime_error(TTF_GetError());
    font = TTF_OpenFont(font_path.c_str(),size);
    if(!font) throw std::runtime_error(SDL_GetError());
    this->x = x;
    this->y = y;
    this->text = text;
    this->color = color;
    surface = TTF_RenderUTF8_Solid(font,this->text.c_str(),color);
    if(!surface) throw std::runtime_error(SDL_GetError());
    //std::cout<<"Text surface: "<< surface->w<<"x"<<surface->h<<std::endl;
    
}

void UIText::init(SDL_Renderer * renderer,EventManager & manager,UI & ui){
    
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    this->renderer = renderer;
    if(!texture) throw std::runtime_error(SDL_GetError());
    
}
const std::string & UIText::getText()const{
    return text;
}
std::pair<int,int> UIText::getSize()const{
    return {surface->w,surface->h};
}
void UIText::setText(const std::string &str){
    text = str;
    if(!text.size())
        return;
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    surface = TTF_RenderUTF8_Solid(font,text.c_str(),color);
    if(!surface) throw std::runtime_error(SDL_GetError());
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if(!texture) throw std::runtime_error(SDL_GetError());
}
SDL_Texture * UIText::render(SDL_Rect & rect,SDL_Renderer * renderer) const {
    if(!text.size())
        return NULL;
    rect.x=x;
    rect.y=y;
    rect.w=surface->w;
    rect.h=surface->h;
    return texture;
}
UIText::~UIText(){
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_Quit();
}