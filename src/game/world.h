// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_WORLD_H__
#define __ENGINE_WORLD_H__

// -----------------------------------------------------------------------------
// Game logic
// -----------------------------------------------------------------------------
class World : public Thread
{
public:
  virtual void        Init(const std::string& script) = 0;
  virtual void        Destroy() = 0;
  virtual void        Render(RenderBuffer *buffer) = 0;
  virtual void        PostEvent(const InputEvent& event) = 0;
};

extern World *world;

#endif /*__ENGINE_WORLD_H__*/
