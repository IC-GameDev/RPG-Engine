// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "engine/common.h"

// -----------------------------------------------------------------------------
Renderer::Renderer()
{
  memset(shaders, 0, sizeof(shaders));
}

// -----------------------------------------------------------------------------
Renderer::~Renderer()
{
  for (size_t i = 0; i < sizeof(shaders) / sizeof(shaders[0]); ++i)
  {
    if (shaders[i])
    {
      delete shaders[i];
      shaders[i] = NULL;
    }
  }
}

// -----------------------------------------------------------------------------
void Renderer::Init()
{
  terrain = new Shader("terrain");
  terrain->Compile("data/shader/terrain.vs.glsl", GL_VERTEX_SHADER);
  terrain->Compile("data/shader/terrain.fs.glsl", GL_FRAGMENT_SHADER);
  terrain->Link();

  particle = new Shader("particle");
  particle->Compile("data/shader/particle.vs.glsl", GL_VERTEX_SHADER);
  particle->Compile("data/shader/particle.fs.glsl", GL_FRAGMENT_SHADER);
  particle->Link();

  object = new Shader("object");
  object->Compile("data/shader/object.vs.glsl", GL_VERTEX_SHADER);
  object->Compile("data/shader/object.fs.glsl", GL_FRAGMENT_SHADER);
  object->Link();
}
