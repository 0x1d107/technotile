#pragma once
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <utility>
#include "Entity.hpp"
#include "json11/json11.hpp"
class Tile;
class World{
    int width;
    int height;
    
    std::vector<Tile*> tiles;

    std::vector<int> grid;
    std::vector<json11::Json> grid_data;
    std::vector<Entity *> entities;
    public:
    static const int tile_size = 32;
    World(int width, int height);
    std::pair<int,int> getSize() const;
    void load(std::string filename);
    const std::vector<Tile*> & getTiles() const;
    int createTile(Tile * tile);
    void createEntity(Entity * entity);
    const std::vector<Entity *> & getEntities() const;
    void update();
    void setTile(int x, int y, int tileId);
    const Tile * getTile(int x, int y) const;
    const json11::Json * getData(int x, int y) const;
    void setData(int x, int y, const json11::Json &json);
    void save(std::string filename);
    virtual ~World();
};
