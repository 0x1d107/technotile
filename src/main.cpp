#include "UI.hpp"
#include "UIImage.hpp"
#include "UIGrid.hpp"
#include "UIText.hpp"
#include "World.hpp"
#include "Tile.hpp"
#include "Entity.hpp"
#include <iostream>
void init_entities(){
    EntityFactory::add(&EntityPlayer::factory);
}
int main(){
    init_entities();
    UI ui;
    //UIImage * kotik = new UIImage("kotik.bmp",100,100);
    World world(32,32); 
    int terrain = world.createTile(new Tile("tiles/terrain.pbm"));
    int spaceship_id = world.createTile(new Tile("tiles/spaceship.pbm"));
    int rover = world.createTile(new Tile("tiles/rover.pbm"));
    int arrow = world.createTile(new Tile("tiles/arrow.pbm"));
    auto player = new EntityPlayer(15,15);
    for(int x=0;x<32;x++){
        for(int y=0;y<32;y++){
            world.setTile(x,y,terrain);
        }
    }
    world.createEntity(player);
    world.setTile(15,16,rover);
    UIGrid* grid = new UIGrid(world);
    ui.addComponent(grid);
    UIText *text = new UIText("ttf/pixel.ttf",0,16,"Tech demo 0.0.1",{0xff,0x00,0x00,0});
    ui.addComponent(text);
    /*
    ui.getManager().addEventHandler(SDL_USEREVENT,{grid,[](UIComponent *owner,const SDL_Event& event){
        if(event.user.code == 0){
            UIGrid *grid = (UIGrid *) owner;
            grid->getWorld().update();
        }
    }});*/
    //ui.addComponent(kotik);
    ui.runEventLoop();
    std::cout << SDL_GetError();
    return 0;
} 
