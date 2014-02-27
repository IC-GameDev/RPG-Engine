// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -----------------------------------------------------------------------------
Chunk::Chunk(Level *level_, glm::ivec2 pos_)
  : level(level_)
  , pos(pos_)
{
}

// -----------------------------------------------------------------------------
Chunk::~Chunk()
{
}

// -----------------------------------------------------------------------------
void Chunk::Load()
{
}

// -----------------------------------------------------------------------------
void Chunk::Save()
{
}

// -----------------------------------------------------------------------------
void Chunk::Feedback(rbDynMesh_t *mesh)
{

}

static float data[] =
{
   0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  32.0f, 0.0f, 32.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  32.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

   0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  32.0f, 0.0f, 32.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
   0.0f, 0.0f, 32.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
};

// -----------------------------------------------------------------------------
void Chunk::Update(rbDynMesh_t *mesh)
{
  mesh->vertData = data;
  mesh->vertCount = 6;
}

// -----------------------------------------------------------------------------
Level::Level(long seed_, const char *name_, const char *path_)
  : seed(seed_)
  , name(name_)
  , path(path_)
  , chunk(this, glm::ivec2(0, 0))
{
}

// -----------------------------------------------------------------------------
Level::~Level()
{
}

// -----------------------------------------------------------------------------
void Level::Generate(Chunk *chunk, glm::ivec2 pos)
{
}

// -----------------------------------------------------------------------------
void Level::Update(const Camera& camera, rbBuffer_t *buffer)
{
  buffer->dynMeshCount = 1;
  chunk.Update(&buffer->dynMesh[0]);

}

// -----------------------------------------------------------------------------
void Level::Feedback(rbBuffer_t *buffer)
{
  chunk.Feedback(&buffer->dynMesh[0]);
}
