extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <iostream>
using namespace std;

class Sprite {
public:
    int health;
};

Sprite* sprite = nullptr;

lua_State* L;

int create_sprite(lua_State* L) {
    sprite = new Sprite;

    sprite->health = lua_tointeger(L, 1);
    lua_pushlightuserdata(L, sprite);

    return 1;
}

int main() {
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "create_sprite", create_sprite);

    luaL_dofile(L, "script.lua");

    lua_getglobal(L, "do_something");
    lua_call(L, 0, 0);

    lua_close(L);

    if (sprite != nullptr) {
        cout << "sprite health: " << sprite->health << endl;
        delete sprite;
    }

    return 0;
}
