// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_LEVEL_H__
#define __ENGINE_LEVEL_H__

/**
 * 64 bit seed value for the generator
 */
typedef unsigned long long Seed;

/// Chunk needs a reference to level
class Level;

/**
 * A chunk represents a portion
 */
class Chunk
{
public:
  /**
   * Creates a new chunk
   * @param level_ Parent level
   * @param pos_ Position of the chunk
   */
  Chunk(Level *level_, glm::ivec2 pos_)
    : level(level_)
    , pos(pos_)
  {
  }

  /**
   * Destroys a chunk
   */
  ~Chunk()
  {
  }

  /**
   * Loads a chunk from storage
   */
  void Load();

  /** 
   * Saves a chunk to storage
   */
  void Save();

  /** 
   * Generates a chunk from scratch
   */
  void Generate();

public:
  /// Size of a chunk
  static const unsigned SIZE = 64;

private:
  /// Parent level
  Level *level;
  /// Chunk position
  glm::ivec2 pos;

  /// Level needs access to chunk data
  friend class Level;
};

/**
 * Quad tree used to store and select chunks
 * It also allows the removal of unneeded chunks
 * Iterative stackless traversal is used to perform all 
 * the operation in O(1) memory
 */
class ChunkTree
{
public:
  /**
   * Creates a new quad tree
   */
  ChunkTree();

  /**
   * Destroyes the tree
   */
  ~ChunkTree();

  /**
   * Inserts a new chunk into the store
   */
  void Insert(Chunk *chunk);

  /**
   * Removes all chunks that are outside a given area
   * @param min Bottom-left corner of the AABB
   * @param max Top-right corner of the AABB
   */
  void Prune(glm::ivec2 min, glm::ivec2 max);

private:
  /**
   * Quad tree node
   */
  struct Node
  {
    /**
     * Sets internal pointers to null
     */
    Node()
      : chunk(NULL)
      , parent(NULL)
      , index(0)
    {
      memset(children, 0, sizeof(children));
    }

    /**
     * Deletes all the children
     */
    ~Node()
    {
      if (chunk)
      {
        delete chunk;
        chunk = NULL;
      }

      for (size_t i = 0; i < 4; ++i)
      {
        if (children[i])
        {
          delete children[i];
          children[i] = NULL;
        }
      }
    }

    /// Index of a chunk or NULL
    Chunk *chunk;

    /// Link to the parent
    Node *parent;

    /// Link to children
    Node *children[4];

    /// Child index
    unsigned index;
  };

  /// Root node of the quad tree
  Node *root;
};

/**
 * A single level
 */
class Level
{
public:
  /**
   * Creates a new empty level
   * @param seed_ Level seed
   * @param name_ Level name
   * @param path_ Location of the cache folder
   */
  Level(Seed seed_, const std::string& name_, const std::string& path_)
    : seed(seed_)
    , name(name_)
    , path(path_)
  {
  }

  /**
   * Destroys the level
   */
  virtual ~Level()
  {
  }

  /**
   * Generate a single chunk
   * @param chunk Destination chunk
   * @param pos Chunk position
   */
  virtual void Generate(Chunk *chunk, glm::ivec2 pos) = 0;

private:
  /// Seed value
  Seed seed;
  /// Level name
  std::string name;
  /// Cache file path
  std::string path;
  /// Quad tree for the chunks
  ChunkTree tree;
};

#endif /*__ENGINE_LEVEL_H__*/
