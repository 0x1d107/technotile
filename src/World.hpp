#pragma once
#include <vector>
#include <string>
#include <SDL2/SDL.h>
struct Tile{
    
    std::string texture_path; 
    SDL_Surface * surface =NULL;
    SDL_Texture * texture= NULL;
    Tile(const std::string& texture_path);
    Tile(const Tile& tile);
    void loadTexture(SDL_Renderer *renderer);
    SDL_Texture *getTexture(SDL_Renderer *renderer) const ;
    ~Tile();
   
};
class World{
    int width;
    int height;
    
    std::vector<Tile*> tiles;
    std::vector<int> grid;
    public:
    static const int tile_size = 32;
    World(int width, int height);
    const std::vector<Tile*> & getTiles() const;
    int createTile(Tile * tile);
    void setTile(int x, int y, int tileId);
    const Tile * getTile(int x, int y) const;
    virtual ~World();
};
