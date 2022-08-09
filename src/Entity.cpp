#include "Entity.hpp"
#include <iostream>
#include <stdexcept>
#include <SDL2/SDL_image.h>
#include "World.hpp"

std::vector<EntityFactory *> EntityFactory::registry;

void EntityFactory::add(EntityFactory *factory){
    factory->set_id(registry.size());
    registry.push_back(factory);
}
void EntityFactory::set_id(int id){
    this->id = id;
}
EntityFactory::EntityFactory(){
}
json11::Json EntityFactory::serializeJson(const Entity *entity){
    auto obj = entity->getFactory().serialize(entity);
    obj["id"] = entity->getFactory().id;
    return obj;
}
Entity * EntityFactory::deserializeJson(const json11::Json &json){
    if(!json.is_object()||!json["id"].is_number()){
        return NULL;
    }
    return EntityFactory::registry[json["id"].int_value()]->deserialize(json);
}
int EntityFactory::getId(){
    return id;
}
Entity::Entity(const std::string &texture_path,int x,int y,int r,const json11::Json &data):texture_path(texture_path),x(x),y(y),rotation(r),data(data){

}

json11::Json::object Entity::to_json()const{
    json11::Json::object obj={
        {"x",x},
        {"y",y},
        {"rotation",rotation},
        {"data",data}
    };
    return obj;
}
void Entity::loadTexture(SDL_Renderer * renderer){
    texture = IMG_LoadTexture(renderer,texture_path.c_str());
    if(!texture)
        throw std::runtime_error(SDL_GetError());
    if(SDL_QueryTexture(texture,NULL,NULL,&width,&height)){
        throw std::runtime_error(SDL_GetError());
    }

}
void Entity::render(SDL_Renderer *renderer,SDL_Rect screen){
    SDL_Rect dst = {x*World::tile_size-screen.x,y*World::tile_size-screen.y,width,height};
    if(SDL_RenderCopyEx(renderer,texture,NULL,&dst,rotation,NULL,SDL_RendererFlip::SDL_FLIP_NONE))
        throw std::runtime_error(SDL_GetError());
}
Entity::~Entity(){
    SDL_DestroyTexture(texture);
}

/// EntityPlayer ///
EntityPlayer::EntityPlayer(int x,int y,int health):Entity("tiles/spaceship.pbm",x,y){
    this->health = health;
}
void EntityPlayer::move(int dx,int dy){
    x+=dx;
    y+=dy;
}

EntityPlayer::PlayerFactory EntityPlayer::factory;
EntityFactory & EntityPlayer::getFactory()const {
    return factory;
}
json11::Json::object EntityPlayer::PlayerFactory::serialize(const Entity * entity){
    auto obj = entity->to_json();
    EntityPlayer * player = (EntityPlayer *)entity;
    obj["hp"] = player->health;
    return obj;
}
Entity * EntityPlayer::PlayerFactory::deserialize(const json11::Json &json){
    auto p = new EntityPlayer(json["x"].int_value(),json["y"].int_value(),json["hp"].int_value());
    p->data = json["data"];
    return p;
}
void EntityPlayer::render(SDL_Renderer * renderer,SDL_Rect screen){
    Entity::render(renderer,screen);
}