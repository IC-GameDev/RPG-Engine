// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -----------------------------------------------------------------------------
CVar Renderer::vpWidth("vpWidth", CVAR_INT, "800", "Width of the viewport");
CVar Renderer::vpHeight("vpHeight", CVAR_INT, "600", "Height of the viewport");
CVar Renderer::vpReload("vpReload", CVAR_BOOL, "true", "Rebuild buffers");

// -----------------------------------------------------------------------------
// Implementation of the renderer
// -----------------------------------------------------------------------------
class RendererImpl : public Renderer
{
public:
                RendererImpl();
  void          Init();
  void          Destroy();
  void          Run();
  void          Frame();

  RenderBuffer *GetBuffer();
  void          SwapBuffers();
  const char   *GetThreadName() { return "renderer"; }

private:
  RenderBuffer buffers[2];
  RenderBuffer *buffer;
  union
  {
    Program *programs[4];
    struct
    {
      Program *p_terrain;
      Program *p_object;
    };
  };

  union
  {
    GLuint textures[10];
  };
};

// -----------------------------------------------------------------------------
static RendererImpl rendererImpl;
Renderer *renderer = &rendererImpl;

// -----------------------------------------------------------------------------
RendererImpl::RendererImpl()
{
  memset(programs, 0, sizeof(programs));
  memset(textures, 0, sizeof(textures));
  buffer = &buffers[0];
}

// -----------------------------------------------------------------------------
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

  glGenTextures(sizeof(textures) / sizeof(textures[0]), textures);
}

// -----------------------------------------------------------------------------
void RendererImpl::Destroy()
{
  glDeleteTextures(sizeof(textures) / sizeof(textures[0]), textures);
  for (size_t i = 0; i < sizeof(programs) / sizeof(programs[0]); ++i)
  {
    if (programs[i])
    {
      delete programs[i];
      programs[i] = NULL;
    }
  }
}

// -----------------------------------------------------------------------------
void RendererImpl::Frame()
{
  glViewport(0, 0, vpWidth.GetInt(), vpHeight.GetInt());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  p_terrain->Bind();
  p_terrain->Uniform("u_proj", buffer->camProj);
  p_terrain->Uniform("u_view", buffer->camView);

  glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
  glEnd();
}

// -----------------------------------------------------------------------------
RenderBuffer *RendererImpl::GetBuffer()
{
  buffers[0].terrain.clear();
  return &buffers[0];
}

// -----------------------------------------------------------------------------
void RendererImpl::SwapBuffers()
{

}

// -----------------------------------------------------------------------------
void RendererImpl::Run()
{

}
