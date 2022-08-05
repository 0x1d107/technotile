#include "Tile.hpp"
#include <iostream>
Tile::Tile(const std::string& texture_path){
    this->texture_path = texture_path;
    this->texture =NULL;
    this->surface=NULL;
}
Tile::Tile(const Tile & tile){
    texture_path = tile.texture_path;
    texture =NULL;
    surface=NULL;
}
void Tile::loadTexture(SDL_Renderer * renderer){
    if(texture)
        return;
    this->surface = IMG_Load(texture_path.c_str());
    if(!surface)throw std::runtime_error(SDL_GetError());
    this->texture = SDL_CreateTextureFromSurface(renderer,surface);
    if(!texture)throw std::runtime_error(SDL_GetError());
    //std::cout<<"texture "<<texture_path<<" size="<<surface->w<<"x"<<surface->h<<std::endl;
}
json11::Json Tile::updateData(const World&world,int x, int y){
    auto data = world.getData(x,y);
    if (data == NULL)
        return json11::Json();
    return *data;
}
SDL_Texture *Tile::getTexture(SDL_Renderer *renderer,SDL_Rect &src,const World& world,int x, int y) const{
    
    auto& data = *world.getData(x,y);
    
    if(data.is_object()&&data["variant"].is_number()&&surface){
        //std::cout<<"texture "<<texture_path<<" size="<<surface->w<<"x"<<surface->h<<std::endl;
        src.x=data["variant"].int_value()*World::tile_size%surface->w;
    }
    return texture;
 }
Tile::~Tile(){
    if(texture)
        SDL_DestroyTexture(texture);
    if(surface)
        SDL_FreeSurface(surface);
}