#include "UIText.hpp"
#include <stdexcept>
UIText::UIText(const std::string &font_path, int x,int y,std::string text,SDL_Color color ){
    if(TTF_Init())
        throw std::runtime_error(TTF_GetError());
    font = TTF_OpenFont(font_path.c_str(),16);
    if(!font) throw std::runtime_error(SDL_GetError());
    this->x = x;
    this->y = y;
    this->text = text;
    this->color = color;
    surface = TTF_RenderUTF8_Solid(font,this->text.c_str(),color);
    if(!surface) throw std::runtime_error(SDL_GetError());
    
}

void UIText::init(SDL_Renderer * renderer,EventManager & manager){
    
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    this->renderer = renderer;
    if(!texture) throw std::runtime_error(SDL_GetError());
    
}
const std::string & UIText::getText()const{
    return text;
}
void UIText::setText(const std::string &str){
    text = str;
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    surface = TTF_RenderUTF8_Solid(font,text.c_str(),color);
    texture = SDL_CreateTextureFromSurface(renderer,surface);
}
SDL_Texture * UIText::render(SDL_Rect & rect,SDL_Renderer * renderer) const {
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