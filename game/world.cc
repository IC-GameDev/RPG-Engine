// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// Implementation of the world
class WorldImpl : public World
{
public:
        WorldImpl();
  void  Load(const std::string& file);
  void  Unload();

private:
  lua_State *L;
};

// Unique world instance
static WorldImpl worldImpl;
World *world = &worldImpl;

// -------------------------------------------------------------------------------------------------
WorldImpl::WorldImpl()
  : L(NULL)
{
}

// -------------------------------------------------------------------------------------------------
void WorldImpl::Load(const std::string& file)
{
  // Create a new lua state
  if (!(L = luaL_newstate()))
  {
    EXCEPT << "Cannot create Lua state";
  }

  // Register lua bindings


  // Run the startup script
  switch (luaL_loadfile(L, file.c_str()))
  {
    case LUA_ERRSYNTAX:
    {
      std::string err(lua_tostring(L, -1));
      lua_pop(L, 1);
      EXCEPT << "Cannot parse Lua file:\n" << err;
      break;
    }
    case LUA_ERRMEM:
    {
      EXCEPT << "Memory allocation failed";
      break;
    }
    case LUA_ERRGCMM:
    {
      EXCEPT << "Error running __gc";
      break;
    }
  }
}

// -------------------------------------------------------------------------------------------------
void WorldImpl::Unload()
{
  if (L)
  {
    lua_close(L);
    L = NULL;
  }
}