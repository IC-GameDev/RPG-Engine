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

  const char   *GetThreadName() { return "world"; }
  void          PostEvent(const InputEvent& evt) { queue.Push(evt); }

private:
  void          HandleKeyEvent(const KeyboardEvent& evt);
  void          HandleMouseEvent(const MouseEvent& evt);
  void          HandleNetworkEvent(const NetworkEvent& evt);

  // System stuff
  lua_State                   *L;
  AsyncQueue<InputEvent, 128>  queue;
  RenderBuffer                *buffer;

  // Actual game state
  CameraTopDown                camera;
};

// -----------------------------------------------------------------------------
// Unique world instance
// -----------------------------------------------------------------------------
static WorldImpl worldImpl;
World *world = &worldImpl;

// -----------------------------------------------------------------------------
WorldImpl::WorldImpl()
  : L(NULL)
  , buffer(NULL)
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
  uint64_t lastFrame, thisFrame;
  float delta = 0.0f;

  lastFrame = thisFrame = engine->GetTime();
  while (threadMngr->IsRunning())
  {
    while (!queue.Empty())
    {
      switch ((event = queue.Pop()).type)
      {
        case EVT_KEYBOARD:
        {
          HandleKeyEvent(event.keyboard);
          break;
        }
        case EVT_MOUSE:
        {
          HandleMouseEvent(event.mouse);
          break;
        }
        case EVT_NETWORK:
        {
          HandleNetworkEvent(event.network);
          break;
        }
      }
    }

    // Update some stuff
    camera.Update(delta);

    // Send data to renderer
    buffer = renderer->SwapBuffers();
    buffer->camProj = camera.GetProj();
    buffer->camView = camera.GetView();

    // Update timers
    lastFrame = thisFrame;
    thisFrame = engine->GetTime();
    delta = (thisFrame - lastFrame) / 1000.0f;
  }
}

// -----------------------------------------------------------------------------
void WorldImpl::HandleKeyEvent(const KeyboardEvent& evt)
{
  switch (evt.key)
  {
    case KEY_A:
    {
      camera.Move(CameraTopDown::LEFT, evt.state);
      break;
    }
    case KEY_W:
    {
      camera.Move(CameraTopDown::UP, evt.state);
      break;
    }
    case KEY_S:
    {
      camera.Move(CameraTopDown::DOWN, evt.state);
      break;
    }
    case KEY_D:
    {
      camera.Move(CameraTopDown::RIGHT, evt.state);
      break;
    }
    default:
    {
      break;
    }
  }
}

// -----------------------------------------------------------------------------
void WorldImpl::HandleMouseEvent(const MouseEvent& evt)
{
}

// -----------------------------------------------------------------------------
void WorldImpl::HandleNetworkEvent(const NetworkEvent& evt)
{
}
