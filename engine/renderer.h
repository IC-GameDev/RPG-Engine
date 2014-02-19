// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_RENDERER_H__
#define __ENGINE_RENDERER_H__

class Renderer
{
public:
  /**
   * Creates a new renderer
   */
  Renderer();

  /**
   * Destroys the renderer
   */
  ~Renderer();

  /**
   * Initialises the renderer
   */
  void Init();

  /**
   * Renders a frame
   */
  void RenderFrame();

private:
  union
  {
    Shader *shaders[3];
    struct
    {
      Shader *terrain;
      Shader *particle;
      Shader *object;
    };
  };
};

#endif /*__ENGINE_RENDERER_H__*/
