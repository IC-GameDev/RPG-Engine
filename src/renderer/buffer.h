// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __RENDERER_BUFFER_H__
#define __RENDERER_BUFFER_H__

// -----------------------------------------------------------------------------
// Information passed to the renderer by the update thread
// -----------------------------------------------------------------------------
typedef struct
{
  glm::vec3    position;
} rbSprite_t;

typedef struct
{
  cacheKey_t   cache;
  uint64_t     uid;
  float       *vertData;
  uint64_t     vertCount;
  glm::mat4    model;
} rbDynMesh_t;

// -----------------------------------------------------------------------------
// Buffer which stores data passed to the renderer
// -----------------------------------------------------------------------------
typedef struct
{
  glm::mat4   camProj;
  glm::mat4   camView;

  size_t      dynMeshCount;
  size_t      spriteCount;

  rbDynMesh_t dynMesh[128];
  rbSprite_t  sprite[4096];
} rbBuffer_t;

#endif /*__RENDERER_BUFFER_H__*/
