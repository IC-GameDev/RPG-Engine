// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -----------------------------------------------------------------------------
// Implementation of the world
// -----------------------------------------------------------------------------
class WorldImpl : public World
{
public:
                WorldImpl();
  void          Init(const std::string& file);
  void          Run();
  void          Destroy();
  void          Render(RenderBuffer *buffer);
  void          PostEvent(const InputEvent& evt);
  const char   *GetThreadName() { return "world"; }

private:
  void          HandleEvent(const InputEvent& evt);

  lua_State                   *L;
  AsyncQueue<InputEvent, 100>  queue;
};

// -----------------------------------------------------------------------------
// Unique world instance
// -----------------------------------------------------------------------------
static WorldImpl worldImpl;
World *world = &worldImpl;

// -----------------------------------------------------------------------------
WorldImpl::WorldImpl()
  : L(NULL)
{
}

// -----------------------------------------------------------------------------
void WorldImpl::Init(const std::string& file)
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

// -----------------------------------------------------------------------------
void WorldImpl::Destroy()
{
  if (L)
  {
    lua_close(L);
    L = NULL;
  }
}

float data[] =
{
  0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  1.0f, 0.0f, 0.0f,
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  1.0f, 1.0f, 0.0f
};

// -----------------------------------------------------------------------------
void WorldImpl::Render(RenderBuffer *buffer)
{
  RBTerrain chunk;
  chunk.data = data;
  chunk.local = glm::mat4(1.0f);
  buffer->terrain.push_back(chunk);
}

// -----------------------------------------------------------------------------
void WorldImpl::Run()
{
  InputEvent event;
  while (threadMngr->IsRunning())
  {
    while (!queue.Empty())
    {
      switch ((event = queue.Pop()).type)
      {
        case EVT_KEYBOARD:
        {
          std::cout << "KeyEvent" << std::endl;
          break;
        }
      }
    }
  }
}

// -----------------------------------------------------------------------------
void WorldImpl::PostEvent(const InputEvent& event)
{
  queue.Push(event);
}

// -----------------------------------------------------------------------------
void WorldImpl::HandleEvent(const InputEvent& event)
{
}
