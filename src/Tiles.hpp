#pragma once
#include "Tile.hpp"
#include "World.hpp"
class TileConveyor:public Tile{
    public:
    TileConveyor();
    json11::Json updateData(const World & world,int x,int y)override;

    SDL_Texture *getTexture(SDL_Renderer *renderer,SDL_Rect &src,const World& world,int x, int y) const override;
};