#include "UI.hpp"
#include "UIImage.hpp"
#include "UIGrid.hpp"
#include "World.hpp"
#include "Tile.hpp"
#include <iostream>
int main(){
    UI ui;
    //UIImage * kotik = new UIImage("kotik.bmp",100,100);
    World world(32,32); 
    int terrain = world.createTile(new Tile("tiles/terrain.pbm"));
    int spaceship_id = world.createTile(new Tile("tiles/spaceship.pbm"));
    int rover = world.createTile(new Tile("tiles/rover.pbm"));
    int arrow = world.createTile(new Tile("tiles/arrow.pbm"));
    for(int x=0;x<32;x++){
        for(int y=0;y<32;y++){
            world.setTile(x,y,terrain);
        }
    }
    world.setTile(16,16,spaceship_id);
    world.setTile(15,16,rover);
    UIGrid* grid = new UIGrid(world);
    ui.addComponent(grid);
    //ui.addComponent(kotik);
    ui.runEventLoop();
    std::cout << SDL_GetError();
    return 0;
} 
