#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

#include "json11/json11.hpp"

class Entity;

class EntityFactory{
    protected:
    public:
    EntityFactory();
    int id = -1;
    static std::vector<EntityFactory *> registry;
    
    void set_id(int id);
    static void add(EntityFactory*factory);
    int getId();
    virtual json11::Json::object serialize(const Entity *entity) = 0;
    virtual Entity * deserialize(const json11::Json &json) =0  ;
    
    static json11::Json serializeJson(const Entity *entity);
    static Entity * deserializeJson(const json11::Json &json);
    virtual ~EntityFactory(){}

};

class Entity{
    protected:
    std::string texture_path;
    SDL_Texture *texture = NULL;
    int width;
    int height;
    int x;
    int y;
    int rotation=0;
    json11::Json data;
    public:
    Entity(const std::string &texture_path,int x,int y,int r = 0,const json11::Json &data = {});
    virtual EntityFactory &getFactory() const = 0;
    virtual json11::Json::object to_json() const;
    virtual void loadTexture(SDL_Renderer * renderer);
    virtual void render(SDL_Renderer *renderer,SDL_Rect screen);
    virtual ~Entity();
};
class EntityPlayer:public Entity{
    public:
    int health=100;
    static class PlayerFactory:public EntityFactory{
        json11::Json::object serialize(const Entity * entity) override;
        Entity * deserialize(const json11::Json &json) override;

    } factory;
    EntityPlayer(int x,int y,int health=100);
    void move(int dx,int dy);
    EntityFactory &getFactory() const override;
    void render(SDL_Renderer * renderer,SDL_Rect screen) override;
};