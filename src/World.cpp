#include "World.hpp"
#include <stdexcept>
#include<SDL2/SDL_image.h>
World::World(int width, int height){
    this->width = width;
    this-> height = height;
    grid.resize(height*width,0);
    tiles.push_back(new Tile("tiles/null.pbm"));
} 

const std::vector<Tile*> & World::getTiles() const{
    return tiles;
}
World::~World(){
   for(auto tile:tiles){
    delete tile;
   } 
}
const Tile * World::getTile(int x,int y) const{
    if(x>=width||x<0||y<0||y>=height)
        return NULL;
    return tiles[grid[y*width+x]];
}
int  World::createTile(Tile * tile){
    tiles.push_back(tile);
    return tiles.size() - 1;
}
void World::setTile(int x, int y, int tileId){
    if(x>=width||x<0||y<0||y>=height||tileId<0||tileId>=(int)tiles.size())
        return ;
    grid[y*width+x] = tileId;

}
Tile::Tile(const std::string& texture_path){
    this->texture_path = texture_path;
}
void Tile::loadTexture(SDL_Renderer * renderer){
    if(texture)
        return;
    this->surface = IMG_Load(texture_path.c_str());
    if(!surface)throw std::runtime_error(SDL_GetError());
    this->texture = SDL_CreateTextureFromSurface(renderer,surface);
    if(!texture)throw std::runtime_error(SDL_GetError());
}
SDL_Texture *Tile::getTexture(SDL_Renderer *renderer) const{
    
    return texture;
 }
Tile::~Tile(){
    if(texture)
        SDL_DestroyTexture(texture);
    if(surface)
        SDL_FreeSurface(surface);
}