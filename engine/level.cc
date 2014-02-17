// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "engine/common.h"

// -----------------------------------------------------------------------------
void Chunk::Load()
{

}

// -----------------------------------------------------------------------------
void Chunk::Save()
{
  
}

// -----------------------------------------------------------------------------
void Chunk::Generate()
{
  
}

// -----------------------------------------------------------------------------
ChunkTree::ChunkTree()
  : root(new Node)
{

}

// -----------------------------------------------------------------------------
ChunkTree::~ChunkTree()
{
  if (root)
  {
    delete root;
    root = NULL;
  }
}

// -----------------------------------------------------------------------------
void ChunkTree::Insert(Chunk *chunk)
{

}

// -----------------------------------------------------------------------------
void ChunkTree::Prune(glm::ivec2 min, glm::ivec2 max)
{

}
