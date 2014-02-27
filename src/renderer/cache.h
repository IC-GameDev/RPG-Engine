// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __RENDERER_CACHE_H__
#define __RENDERER_CACHE_H__

// -----------------------------------------------------------------------------
// Least Recently Used cache
// -----------------------------------------------------------------------------
typedef struct
{
  uint64_t  id;
  uint64_t  frame;
} cacheKey_t;

// -----------------------------------------------------------------------------
class Cache
{
public:
  virtual void         Init() = 0;
  virtual void         Destroy() = 0;
  virtual void         Flush() = 0;
  virtual void         Update() = 0;
  virtual cacheKey_t   Insert(GLuint object) = 0;
  virtual GLuint      *Fetch(const cacheKey_t& key) = 0;
};

// -----------------------------------------------------------------------------
extern Cache *cache;

#endif
