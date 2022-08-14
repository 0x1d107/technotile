#include "Tiles.hpp"
TileConveyor::TileConveyor():Tile("tiles/arrow.pbm"){

}
json11::Json TileConveyor::updateData(const World & world,int x,int y){
    auto data_ptr = world.getData(x,y);
    if(!data_ptr||!data_ptr->is_object()){
        return json11::Json();
    }
    auto data = *data_ptr;
    int rotation = data["variant"].is_number()?data["variant"].int_value():0;
    int offsets[4][2]={
        {1,0},
        {0,-1},
        {-1,0},
        {0,1}
    };
    json11::Json input;
    for(int i=0;i<4;i++){
        int dir = (rotation+i+2)%4;
        if(dir%4 == rotation%4)
            continue;
        auto adj_input_data_ptr = world.getData(x+offsets[dir][0],y+offsets[dir][1]);
        if(!adj_input_data_ptr||!adj_input_data_ptr->is_object())
            continue;
        auto adj = *adj_input_data_ptr;
        auto adj_rot = adj["variant"].is_number()?adj["variant"].int_value()%4:0;
        if(!adj["output"].is_object()||  adj_rot!= (dir+2)%4)
            continue;
        
        input = adj["output"];
        break;
    }

    
    return json11::Json::object{{"output",data["input"]},{"input",input},{"variant",rotation}};
}

SDL_Texture * TileConveyor::getTexture(SDL_Renderer *renderer,SDL_Rect &src,const World& world,int x, int y) const {
    auto texture = Tile::getTexture(renderer,src,world,x,y);
    if(!world.getData(x,y))
        return texture;
    auto  data = *world.getData(x,y);
    if(data["input"].is_object())
        SDL_SetTextureColorMod(texture,0xfc,0x69,0x00);
    else if(data["output"].is_object())
        SDL_SetTextureColorMod(texture,0x00,0x73,0xf7);
    else 
        SDL_SetTextureColorMod(texture,0xff,0xff,0xff);
    return texture;
}