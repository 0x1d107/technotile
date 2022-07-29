#include "UI.hpp"
#include "UIImage.hpp"
#include "UIGrid.hpp"
#include "World.hpp"
#include <iostream>
int main(){
    UI ui;
    //UIImage * kotik = new UIImage("kotik.bmp",100,100);
    World world(32,32); 
    int spaceship_id = world.createTile(new Tile("tiles/spaceship.pbm"));
    int terrain = world.createTile(new Tile("tiles/terrain.pbm"));
    world.setTile(16,16,spaceship_id);
    UIGrid* grid = new UIGrid(world);
    ui.addComponent(grid);
    //ui.addComponent(kotik);
    ui.runEventLoop();
    std::cout << SDL_GetError();
    return 0;
} 
