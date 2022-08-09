#pragma once
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <utility>
#include "World.hpp"

class Tile{
    protected:
    std::string texture_path; 
    SDL_Texture * texture= NULL;
    int width;
    int height;
    public:
    Tile(const std::string& texture_path);
    Tile(const Tile& tile);
    void loadTexture(SDL_Renderer *renderer);
    virtual SDL_Texture *getTexture(SDL_Renderer *renderer,SDL_Rect &src,const World& world,int x, int y) const ;
    virtual json11::Json updateData(const World &world,int x,int y);

    virtual ~Tile();
   
};


