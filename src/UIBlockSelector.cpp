#include "UIBlockSelector.hpp"
#include "Tile.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
UIBlockSelector::UIBlockSelector(int x,int y,World & world,UIGrid *grid):world(&world),grid(grid),x(x),y(y){

}
int UIBlockSelector::getSelection(){
    return sel;
}
UIGrid * UIBlockSelector::getGrid(){
    return grid;
}

void UIBlockSelector::init(SDL_Renderer *renderer,EventManager& manager,UI & ui){
    area = new UITextArea("ttf/pixel.ttf",10, 544,":",[this,renderer](const std::string & str){
        std::cout<<"> "<<str<<std::endl;
        std::stringstream ss(str);
        std::string cmd;
        ss>>cmd;
        if(cmd == "save"){
            std::string name = "world.json";
            if(!ss.eof())
                ss>>name;
            this->world->save(name);
        }else if(cmd == "load"){
            std::string name = "world.json";
            if(!ss.eof())
                ss>>name;
            this->world->load(name);
            for(auto e:this->world->getEntities()){
                e->loadTexture(renderer);
            }

        }
    });
    ui.addComponent(area);
    manager.addEventHandler(SDL_KEYDOWN,{this,[](UIComponent *owner,const SDL_Event & ev){
        if(SDL_IsTextInputActive()){
            return;
        }
        UIBlockSelector *selector = (UIBlockSelector *)owner;
        if(ev.key.keysym.sym == SDLK_SEMICOLON){
            selector->area->startInput(":");
        }
    }});

    manager.addEventHandler(SDL_KEYDOWN,{this,[](UIComponent *owner,const SDL_Event & ev){
        if(SDL_IsTextInputActive()){
            return;
        }
        UIBlockSelector *selector = (UIBlockSelector *)owner;
        if(ev.key.keysym.sym >=SDLK_1&& ev.key.keysym.sym <=SDLK_9){
            selector->select(ev.key.keysym.sym- SDLK_1);
        }
    }});
    manager.addEventHandler(SDL_MOUSEBUTTONDOWN,{this,[](UIComponent *owner,const SDL_Event & ev){
        
        UIBlockSelector *selector = (UIBlockSelector *)owner;
        UIGrid *grid = selector->getGrid();
        int px=(grid->x+ev.button.x)/World::tile_size; 
        int py=(grid->y+ev.button.y)/World::tile_size; 
        if(ev.button.button==SDL_BUTTON_LEFT){
            int sel = selector->getSelection(); 
            if(sel>=0&&sel<grid->getWorld().getTiles().size())
                grid->getWorld().setTile(px,py,sel);
        }else if(ev.button.button==SDL_BUTTON_RIGHT){

            grid->getWorld().setTile(px,py,1);
        }else if(ev.button.button == SDL_BUTTON_MIDDLE){
            auto data_ptr = grid->getWorld().getData(px,py);
            if(!data_ptr)
                return;
            const json11::Json &data = *data_ptr;
            if(data.is_object()){
                auto data_obj=json11::Json::object (data.object_items());
                if(data["variant"].is_number())
                    data_obj["variant"] = (data["variant"].int_value()+1);
                else
                    data_obj["variant"] = 0;
                grid->getWorld().setData(px,py,data_obj);
            }
        }
    }});
    
}
void UIBlockSelector::select(int i){
    sel = i;
}
SDL_Texture * UIBlockSelector::render(SDL_Rect &dst,SDL_Renderer* renderer)const{
    for(int i=0;i<world->getTiles().size();i++){
        SDL_Rect src={0,0,World::tile_size,World::tile_size};
        SDL_Rect dst = {x+i*World::tile_size,y,World::tile_size,World::tile_size};
        SDL_Texture * tx = world->getTiles()[i]->getTexture(renderer,src,*world,-1,-1);
        if(tx){
            if(SDL_RenderCopy(renderer,tx,&src,&dst)){
                throw std::runtime_error(SDL_GetError());
            }
            if(i==sel){
                SDL_SetRenderDrawColor(renderer,255,0,0,255);
                SDL_RenderDrawRect(renderer,&dst);
            }
        }
    }
    return NULL;
}