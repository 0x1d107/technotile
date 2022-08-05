#include "World.hpp"
#include "Tile.hpp"
#include <stdexcept>
#include<SDL2/SDL_image.h>
#include <fstream>
#include <sstream>
World::World(int width, int height){
    this->width = width;
    this-> height = height;
    grid.resize(height*width,0);
    tiles.push_back(new Tile("tiles/null.pbm"));
    grid_data.resize(height*width,json11::Json::object());
} 
std::pair<int,int> World::getSize() const{
    return {width,height};
}
void World::load(std::string filename){
    std::ifstream world_file(filename);
    std::stringstream world_ss;
    world_ss << world_file.rdbuf();
    std::string err;
    json11::Json world_json = json11::Json::parse(world_ss.str(),err);
    if(err.size()){
        throw std::runtime_error(err);
    }
    width = world_json["width"].int_value();
    height = world_json["height"].int_value();
    grid.clear();
    for(auto t:world_json["grid"].array_items()){
        grid.push_back(t.int_value());
    }
    grid_data.clear();
    for(auto t:world_json["data"].array_items()){
        grid_data.push_back(t);
    }
    world_file.close();
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
    grid_data[y*width+x] = json11::Json::object();

}
const json11::Json* World::getData(int x,int y) const {
    if(x>=width||x<0||y<0||y>=height)
        return NULL;
    return &grid_data[y*width+x];
}
void World::setData(int x,int y,const json11::Json& json){

    if(x>=width||x<0||y<0||y>=height)
        return ;
    grid_data[y*width+x] = json;
}
void World::save(std::string filename){
    std::ofstream world_file(filename);
    json11::Json world_json=json11::Json::object{
        {"width",width},
        {"height",height},
        {"grid",grid},
        {"data",grid_data},
    };
    world_file << world_json.dump() <<std::endl;
    world_file.close();
}