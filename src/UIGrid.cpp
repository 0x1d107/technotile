#include "UIGrid.hpp"
#include "Tile.hpp"
#include <iostream>
UIGrid::UIGrid(World & world){
    this->world = &world;
}

void UIGrid::init(SDL_Renderer *renderer,EventManager &manager){
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
    manager.addEventHandler(SDL_KEYDOWN,{this,[](UIComponent *owner,const SDL_Event & ev){
        UIGrid *grid = (UIGrid *)owner;
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
            case SDLK_j:
            grid->world->save("world.json");
            break;
            case SDLK_l:
            grid->world->load("world.json");
            break;


        }
    }});
    manager.addEventHandler(SDL_MOUSEBUTTONDOWN,{this,[](UIComponent *owner,const SDL_Event & ev){
        
        UIGrid *grid = (UIGrid *)owner;
        int px=(grid->x+ev.button.x)/World::tile_size; 
        int py=(grid->y+ev.button.y)/World::tile_size; 
        if(ev.button.button==SDL_BUTTON_LEFT){
            grid->world->setTile(px,py,4);
        }else if(ev.button.button==SDL_BUTTON_RIGHT){

            grid->world->setTile(px,py,1);
        }else if(ev.button.button == SDL_BUTTON_MIDDLE){
            auto data_ptr = grid->world->getData(px,py);
            if(!data_ptr)
                return;
            const json11::Json &data = *data_ptr;
            if(data.is_object()){
                auto data_obj=json11::Json::object (data.object_items());
                if(data["variant"].is_number())
                    data_obj["variant"] = (data["variant"].int_value()+1);
                else
                    data_obj["variant"] = 0;
                grid->world->setData(px,py,data_obj);
            }
        }
    }});
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
                SDL_RenderCopy(renderer,texture,&src,&dst);
            }
        }
    }
    return NULL;
}
