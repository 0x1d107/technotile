#include "UIGrid.hpp"
#include <iostream>
UIGrid::UIGrid(World & world){
    this->world = &world;
}

void UIGrid::init(SDL_Renderer *renderer,EventManager &manager){
    auto tiles = world->getTiles();
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


        }
    }});
    manager.addEventHandler(SDL_MOUSEBUTTONDOWN,{this,[](UIComponent *owner,const SDL_Event & ev){
        
        UIGrid *grid = (UIGrid *)owner;
        grid->world->setTile((grid->x+ev.button.x)/World::tile_size,(grid->y+ev.button.y)/World::tile_size,2);
    }});
}
SDL_Texture * UIGrid::render(SDL_Rect & rect,SDL_Renderer * renderer)  const {
    SDL_Rect viewport;
    SDL_RenderGetViewport(renderer,&viewport);
    //SDL_Texture * target = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,viewport.w,viewport.h);
    //SDL_SetRenderTarget(renderer,target);
    SDL_Rect src = {0,0,World::tile_size,World::tile_size};
    for(int i=0;i<=viewport.w/World::tile_size;i++){
        for(int j=0;j<=viewport.h/World::tile_size;j++){
            const Tile *tile = world->getTile(i+x/World::tile_size,j+y/World::tile_size);
            if(!tile)
                continue;
            SDL_Texture *texture = tile->getTexture(renderer);
            SDL_Rect dst = {i*World::tile_size - x%World::tile_size,j*World::tile_size -y%World::tile_size,World::tile_size,World::tile_size};
            //std::cout << "texture is " << (tile->texture?"NOT NULL":"NULL")<<std::endl;
            if (texture){
                SDL_RenderCopy(renderer,texture,&src,&dst);
                //std::cout<<"rendercopy!\n";    
            }
        }
    }
    //SDL_SetRenderTarget(renderer,NULL);
    return NULL;
}
