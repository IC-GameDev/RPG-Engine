// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_RENDERER_H__
#define __ENGINE_RENDERER_H__

// -----------------------------------------------------------------------------
// The cool part of the engine
// -----------------------------------------------------------------------------
class Renderer
{
public:
  virtual void          Init() = 0;
  virtual void          Destroy() = 0;
  virtual void          Frame() = 0;
  virtual rbBuffer_t   *SwapBuffers() = 0;

  static CVar           vpWidth;
  static CVar           vpHeight;
  static CVar           vpReload;
};

extern Renderer *renderer;

#endif /*__ENGINE_RENDERER_H__*/
