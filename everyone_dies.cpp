extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <memory>
#include <iostream>
using std::cout;
using std::endl;

#include <vector>
#include <string>

class Sprite {
public:
    std::string name;
    int health;
};

std::vector<std::unique_ptr<Sprite>> sprites;

int create_sprite(lua_State* L) {
    Sprite* sprite = new Sprite;

    lua_pushstring(L, "name");
    lua_gettable(L, -2);
    sprite->name = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "health");
    lua_gettable(L, -2);
    sprite->health = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_pushlightuserdata(L, sprite);
    sprites.push_back(std::unique_ptr<Sprite>(sprite));

    return 1;
}

int sprite_get_name(lua_State* L) {
    const Sprite* sprite = static_cast<const Sprite*>(lua_touserdata(L, 1));

    lua_pushstring(L, sprite->name.c_str());

    return 1;
}

int sprite_get_health(lua_State* L) {
    const Sprite* sprite = static_cast<const Sprite*>(lua_touserdata(L, 1));

    lua_pushnumber(L, sprite->health);

    return 1;
}

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "create_sprite", create_sprite);
    lua_register(L, "sprite_get_name", sprite_get_name);
    lua_register(L, "sprite_get_health", sprite_get_health);

    luaL_dofile(L, "script.lua");

    lua_getglobal(L, "do_something");
    lua_call(L, 0, 0);

    lua_close(L);

    for (auto& sprite: sprites) {
        cout << "sprite name: " << sprite->name << "; health: " << sprite->health << endl;
    }

    return 0;
}
