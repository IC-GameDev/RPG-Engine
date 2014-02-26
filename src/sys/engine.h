// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __SYS_ENGINE_H__
#define __SYS_ENGINE_H__

// -----------------------------------------------------------------------------
// Abstract interface to platform-specific features
// -----------------------------------------------------------------------------
class Engine
{
public:
  virtual void        Init()     = 0;
  virtual void        Run()      = 0;
  virtual void        Destroy()  = 0;
  virtual uint64_t    GetTime()  = 0;
  virtual void        Quit() { running = false; }

  static CVar       wndWidth;
  static CVar       wndHeight;
  static CVar       wndTitle;
  static CVar       wndReload;
  static CVar       wndType;

protected:
  lua_State        *L;
  bool              focus;
  volatile bool     running;
};

// -----------------------------------------------------------------------------
// Unique engine instance
// -----------------------------------------------------------------------------
extern Engine *engine;

#endif /*__GAME_GAME_H__*/