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

  const char   *GetThreadName() { return "world"; }
  void          PostEvent(const InputEvent& evt) { queue.Push(evt); }

private:
  void          HandleKeyEvent(const KeyboardEvent& evt);
  void          HandleMouseEvent(const MouseEvent& evt);
  void          HandleNetworkEvent(const NetworkEvent& evt);

  // System stuff
  lua_State                      *L;
  AsyncQueue<InputEvent, 128>     queue;
  rbBuffer_t                     *buffer;

  // Actual game state
  CameraTopDown                   camera;
  Level                           level;
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
  , level(0, "test", "./save/")
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

static float data[] =
{
  0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  1.0f, 0.0f, 0.0f,
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  1.0f, 1.0f, 0.0f
};

// -----------------------------------------------------------------------------
void WorldImpl::Run()
{
  InputEvent event;
  uint64_t lastFrame, thisFrame;
  float delta = 0.0f;

  lastFrame = thisFrame = engine->GetTime();
  while (engine->IsRunning())
  {
    // Process input from renderer
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

    // Get a new buffer
    buffer = renderer->SwapBuffers();
    buffer->camProj = camera.GetProj();
    buffer->camView = camera.GetView();

    // Process feedback from the renderer
    level.Feedback(buffer);

    // Clear the buffer & add new object
    camera.Update(delta);
    level.Update(camera, buffer);

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
