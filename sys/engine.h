// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __SYS_ENGINE_H__
#define __SYS_ENGINE_H__

// Class providing an interface to platform-specific features
class Engine
{
public:
                    Engine();

  virtual void      Init()    = 0;
  virtual void      Run()     = 0;
  virtual void      Destroy() = 0;
  virtual uint64_t  GetTime() = 0;

protected:
  bool          fullscreen;
  bool          focus;
  volatile bool running;
  glm::ivec2    viewport;
  std::string   title;
};

// Unique engine instance
extern Engine *engine;

#endif /*__GAME_GAME_H__*/