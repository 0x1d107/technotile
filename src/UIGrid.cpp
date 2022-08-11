#include "UIGrid.hpp"
#include "Tile.hpp"
#include <iostream>
UIGrid::UIGrid(World & world){
    this->world = &world;
}

void UIGrid::init(SDL_Renderer *renderer,EventManager &manager, UI&ui){
    auto tiles = world->getTiles();
    auto world_size = world->getSize();
    SDL_Rect viewport;
    SDL_RenderGetViewport(renderer,&viewport);
    int cx = (world_size.first*World::tile_size - viewport.w)/2;
    int cy = (world_size.second*World::tile_size - viewport.h)/2;
    x = cx;
    y= cy;
    for (auto tile:tiles){
        tile->loadTexture(renderer);
    }
    for(auto entity:world->getEntities()){
        entity->loadTexture(renderer);
    }
    this->renderer = renderer;
    manager.addEventHandler(SDL_KEYDOWN,{this,[](UIComponent *owner,const SDL_Event & ev){
        if(SDL_IsTextInputActive())
            return;
        UIGrid *grid = (UIGrid *)owner;
        EntityPlayer* player = (EntityPlayer *)grid->world->getEntities()[0];
        switch(ev.key.keysym.sym){
            case SDLK_s:
            grid->y+=16;
            break;
            case SDLK_w:
            grid->y-=16;
            break;
            case SDLK_d:
            grid->x+=16;
            break;
            case SDLK_a:
            grid->x-=16;
            break;
            case SDLK_UP:
            player->move(0,-1);
            break;
            case SDLK_DOWN:
            player->move(0,1);
            break;
            case SDLK_LEFT:
            player->move(-1,0);
            break;
            case SDLK_RIGHT:
            player->move(1,0);
            break;    

        }
    }});
}
World & UIGrid::getWorld(){
    return *world;
}
SDL_Texture * UIGrid::render(SDL_Rect & rect,SDL_Renderer * renderer)  const {
    SDL_Rect viewport;
    SDL_RenderGetViewport(renderer,&viewport);
    for(int i=0;i<=viewport.w/World::tile_size;i++){
        for(int j=0;j<=viewport.h/World::tile_size;j++){
            SDL_Rect src = {0,0,World::tile_size,World::tile_size};
            const Tile *tile = world->getTile(i+x/World::tile_size,j+y/World::tile_size);
            if(!tile)
                continue;
            SDL_Texture *texture = tile->getTexture(renderer,src,*world,i+x/World::tile_size,j+y/World::tile_size);
            SDL_Rect dst = {i*World::tile_size - x%World::tile_size,j*World::tile_size -y%World::tile_size,World::tile_size,World::tile_size};
            if (texture){
                if(SDL_RenderCopy(renderer,texture,&src,&dst))
                    throw std::runtime_error(SDL_GetError());
            }
        }
    }
    for(auto & e:world->getEntities()){
        e->render(renderer,{x,y,viewport.w,viewport.h});
    }
    return NULL;
}
