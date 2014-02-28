// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_LEVEL_H__
#define __ENGINE_LEVEL_H__

// -----------------------------------------------------------------------------
// Chunks store a heightmap
// -----------------------------------------------------------------------------
class Level;

class Chunk
{
public:
                   Chunk(Level *level_, glm::ivec2 pos_);
                  ~Chunk();

  void             Load();
  void             Save();
  void             Feedback(rbDynMesh_t *mesh);
  void             Update(rbDynMesh_t *mesh);
  void             BuildMesh();

private:
  Level           *level;
  float           *vertData;
  float           *heightMap;
  glm::ivec2       pos;
  cacheKey_t       cache;
  friend class     Level;
  static const int SIZE = 32;
};

// -----------------------------------------------------------------------------
class Level
{
public:
                    Level(long seed, const char *name, const char *path);
                   ~Level();

  void              Generate(Chunk *chunk, glm::ivec2 pos);
  void              Update(const Camera& camera, rbBuffer_t *buffer);
  void              Feedback(rbBuffer_t *buffer);

private:
  long              seed;
  const char       *name;
  const char       *path;
  Chunk             chunk;
};

#endif /*__ENGINE_LEVEL_H__*/
