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

  rbBuffer_t   *SwapBuffers();

private:
  void          RenderSprite(rbSprite_t *sprite);
  void          RenderDynMesh(rbDynMesh_t *mesh);

  rbBuffer_t    buffers[2];
  rbBuffer_t   *front;
  rbBuffer_t   *back;
  Signal       *frontSignal;
  Signal       *backSignal;

  union
  {
    Program *programs[2];
    struct
    {
      Program *p_sprite;
      Program *p_dyn_mesh;
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
  : front(&buffers[0])
  , back(&buffers[1])
{
  memset(programs, 0, sizeof(programs));
  memset(textures, 0, sizeof(textures));
  buffers[0].index = 0;
  buffers[1].index = 1;
}

// -----------------------------------------------------------------------------
void RendererImpl::Init()
{
  frontSignal = threadMngr->CreateSignal();
  backSignal = threadMngr->CreateSignal();

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
      "sprite",
      {
        { "assets/shader/sprite.vs.glsl", GL_VERTEX_SHADER },
        { "assets/shader/sprite.fs.glsl", GL_FRAGMENT_SHADER }
      }
    },
    {
      "dyn_mesh",
      {
        { "assets/shader/dyn_mesh.vs.glsl", GL_VERTEX_SHADER },
        { "assets/shader/dyn_mesh.fs.glsl", GL_FRAGMENT_SHADER }
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
  backSignal->Wait();

  glViewport(0, 0, vpWidth.GetInt(), vpHeight.GetInt());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  vpReload.ClearModified();

  // Render sprites
  p_sprite->Bind();
  p_sprite->Uniform("u_proj", front->camProj);
  p_sprite->Uniform("u_view", front->camView);
  for (size_t i = 0; i < front->spriteCount; ++i)
  {
    RenderSprite(&front->sprite[i]);
  }

  // Render dynamic meshes
  p_dyn_mesh->Bind();
  p_dyn_mesh->Uniform("u_proj", front->camProj);
  p_dyn_mesh->Uniform("u_view", front->camView);
  for (size_t i = 0; i < front->dynMeshCount; ++i)
  {
    RenderDynMesh(&front->dynMesh[i]);
  }

  frontSignal->Notify();
}

// -----------------------------------------------------------------------------
rbBuffer_t *RendererImpl::SwapBuffers()
{
  rbBuffer_t *tmp;

  frontSignal->Wait();

  tmp = front;
  front = back;
  back = tmp;

  backSignal->Notify();

  return back;
}

// -----------------------------------------------------------------------------
void RendererImpl::RenderSprite(rbSprite_t *sprite)
{

}

// -----------------------------------------------------------------------------
void RendererImpl::RenderDynMesh(rbDynMesh_t *mesh)
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 32, mesh->vertData);
  glDrawArrays(GL_TRIANGLES, 0, mesh->vertCount);
  glDisableClientState(GL_VERTEX_ARRAY);
}
