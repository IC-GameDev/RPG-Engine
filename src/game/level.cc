// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -----------------------------------------------------------------------------
Chunk::Chunk(Level *level_, glm::ivec2 pos_)
  : level(level_)
  , vertData(NULL)
  , heightMap(NULL)
  , pos(pos_)
{
  heightMap = new float[SIZE * SIZE];
  for (int i = 0; i < SIZE; ++i)
  {
    for (int j = 0; j < SIZE; ++j)
    {
      heightMap[i * SIZE + j] = sin(i / 10.0f) * cos(j / 10.0f) * 3.0f;
    }
  }
  BuildMesh();
}

// -----------------------------------------------------------------------------
Chunk::~Chunk()
{
  if (vertData)
  {
    delete[] vertData;
  }

  if (heightMap)
  {
    delete[] heightMap;
  }
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

// -----------------------------------------------------------------------------
void Chunk::Update(rbDynMesh_t *mesh)
{
  //if (vertData)
  //{
  //  delete[] vertData;
  //}

  //BuildMesh();
  mesh->vertData = vertData;
  mesh->vertCount = SIZE * SIZE * 6;
}

// -----------------------------------------------------------------------------
void Chunk::BuildMesh()
{
  float *data;

  data = vertData = new float[SIZE * SIZE * 6 * 8];
  for (int i = 0; i < SIZE - 1; ++i)
  {
    for (int j = 0; j < SIZE - 1; ++j)
    {
      float h00 = heightMap[(i + 0) * SIZE + j + 0];
      float h01 = heightMap[(i + 0) * SIZE + j + 1];
      float h10 = heightMap[(i + 1) * SIZE + j + 0];
      float h11 = heightMap[(i + 1) * SIZE + j + 1];

      data[0] = i + 0; data[1] =  h00; data[2] = j + 0;
      data[3] =  0.0f; data[4] = 1.0f; data[5] =  0.0f;
      data[6] =  0.0f; data[7] = 0.0f;
      data += 8;

      data[0] = i + 1; data[1] =  h10; data[2] = j + 0;
      data[3] =  0.0f; data[4] = 1.0f; data[5] =  0.0f;
      data[6] =  1.0f; data[7] = 0.0f;
      data += 8;

      data[0] = i + 1; data[1] =  h11; data[2] = j + 1;
      data[3] =  0.0f; data[4] = 1.0f; data[5] =  0.0f;
      data[6] =  1.0f; data[7] = 1.0f;
      data += 8;

      data[0] = i + 0; data[1] =  h00; data[2] = j + 0;
      data[3] =  0.0f; data[4] = 1.0f; data[5] =  0.0f;
      data[6] =  0.0f; data[7] = 0.0f;
      data += 8;

      data[0] = i + 1; data[1] =  h11; data[2] = j + 1;
      data[3] =  0.0f; data[4] = 1.0f; data[5] =  0.0f;
      data[6] =  1.0f; data[7] = 1.0f;
      data += 8;

      data[0] = i + 0; data[1] =  h01; data[2] = j + 1;
      data[3] =  0.0f; data[4] = 1.0f; data[5] =  0.0f;
      data[6] =  0.0f; data[7] = 1.0f;
      data += 8;
    }
  }
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
