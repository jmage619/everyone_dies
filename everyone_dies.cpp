extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

lua_State* L;

int main() {
    L = luaL_newstate();
    luaL_openlibs(L);

    luaL_dofile(L, "script.lua");

    lua_getglobal(L, "do_something");
    lua_call(L, 0, 0);

    lua_close(L);
    return 0;
}
