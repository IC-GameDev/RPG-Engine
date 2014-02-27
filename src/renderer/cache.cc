// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -----------------------------------------------------------------------------
class CacheImpl : public Cache
{
public:
  void         Init();
  void         Destroy();
  void         Flush();
  void         Update();
  cacheKey_t   Insert(GLuint object);
  GLuint      *Fetch(const cacheKey_t& key);
};

// -----------------------------------------------------------------------------
static CacheImpl cacheImpl;
Cache *cache = &cacheImpl;

// -----------------------------------------------------------------------------
void CacheImpl::Init()
{
}

// -----------------------------------------------------------------------------
void CacheImpl::Destroy()
{
}

// -----------------------------------------------------------------------------
void CacheImpl::Flush()
{
}

// -----------------------------------------------------------------------------
void CacheImpl::Update()
{
}

// -----------------------------------------------------------------------------
cacheKey_t CacheImpl::Insert(GLuint object)
{

}

// -----------------------------------------------------------------------------
GLuint *CacheImpl::Fetch(const cacheKey_t& key)
{
  return NULL;
}
