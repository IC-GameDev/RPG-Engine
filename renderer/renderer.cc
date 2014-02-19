// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

class RendererImpl : public Renderer
{
public:
       RendererImpl();
  void Init();
  void Destroy();
  void Frame();

private:
  union
  {
    Program *programs[4];
    struct
    {
      Program *p_dfr_terrain;
      Program *p_dfr_object;
      Program *p_light_point;
      Program *p_light_dir;
    };
  };
};

// Renderer instance
static RendererImpl rendererImpl;
Renderer *renderer = &rendererImpl;

// -------------------------------------------------------------------------------------------------
RendererImpl::RendererImpl()
{
  memset(programs, 0, sizeof(programs));
}

// -------------------------------------------------------------------------------------------------
void RendererImpl::Init()
{
  struct
  {
    const char *name;
    struct
    {
      const char *file;
      GLenum type;
    } src[10];
  }
  desc[] =
  {
    {
      "terrain",
      {
        { "assets/shader/terrain.vs.glsl", GL_VERTEX_SHADER },
        { "assets/shader/terrain.fs.glsl", GL_FRAGMENT_SHADER }
      }
    },
    {
      "object",
      {
        { "assets/shader/object.vs.glsl", GL_VERTEX_SHADER },
        { "assets/shader/object.fs.glsl", GL_FRAGMENT_SHADER }
      }
    },
    {
      "light_point",
      {
        { "assets/shader/light_point.vs.glsl", GL_VERTEX_SHADER },
        { "assets/shader/light_point.fs.glsl", GL_FRAGMENT_SHADER }
      }
    },
    {
      "light_dir",
      {
        { "assets/shader/light_dir.vs.glsl", GL_VERTEX_SHADER },
        { "assets/shader/light_dir.fs.glsl", GL_FRAGMENT_SHADER }
      }
    }
  };

  for (size_t i = 0; i < sizeof(desc) / sizeof(desc[0]); ++i)
  {
    programs[i] = new Program(desc[i].name);
    for (size_t j = 0; desc[i].src[j].file; ++j)
    {
      programs[i]->Compile(desc[i].src[j].file, desc[i].src[j].type);
    }
    programs[i]->Link();
  }
}

// -------------------------------------------------------------------------------------------------
void RendererImpl::Destroy()
{
  for (size_t i = 0; i < sizeof(programs) / sizeof(programs[0]); ++i)
  {
    if (programs[i])
    {
      delete programs[i];
      programs[i] = NULL;
    }
  }
}

// -------------------------------------------------------------------------------------------------
void RendererImpl::Frame()
{

}
