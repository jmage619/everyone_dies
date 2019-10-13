extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <cstdlib>
#include <ctime>
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

int sprite_new(lua_State* L) {
    Sprite* sprite = static_cast<Sprite*>(lua_newuserdata(L, sizeof(Sprite)));

    lua_pushstring(L, "name");
    lua_gettable(L, -3);
    sprite->name = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "health");
    lua_gettable(L, -3);
    sprite->health = lua_tointeger(L, -1);
    lua_pop(L, 1);

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

const luaL_Reg sprite_lib[] = {
    {"new", sprite_new},
    {"get_name", sprite_get_name},
    {"get_health", sprite_get_health},
    {NULL, NULL}
};

int main() {
    srand(time(nullptr));
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // didnt work in Lua 5.3
    //luaL_openlib(L, "Sprite", sprite_lib, 0);
    lua_newtable(L);
    luaL_setfuncs(L, sprite_lib, 0);
    lua_setglobal(L, "Sprite");

    lua_newtable(L);
    lua_setglobal(L, "sprites");

    luaL_dofile(L, "script.lua");

    lua_getglobal(L, "init");
    lua_call(L, 0, 0);

    while (true) {
        lua_getglobal(L, "sprites");
        int len = luaL_len(L, -1);
        if (len == 0)
            break;

        int index = rand() % len + 1;
        lua_rawgeti(L, -1, index);
        Sprite* s = static_cast<Sprite*>(lua_touserdata(L, -1));
        int health = --s->health;
        lua_pop(L, 1);

        lua_getglobal(L, "handle_damage");
        lua_pushnumber(L, index);
        lua_call(L, 1, 0);

        /*if (health == 0) {
            sprites.erase(sprites.begin() + index);
        }
        */
        lua_pop(L, 1); // pop sprites array
    }

    lua_close(L);
    return 0;
}
