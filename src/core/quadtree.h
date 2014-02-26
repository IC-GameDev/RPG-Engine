// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_QUADTREE_H__
#define __ENGINE_QUADTREE_H__

template <class T>
class QuadTree
{
public:
  /**
   * Creates a new empty quadtree
   */
   QuadTree();

   /**
    * Builds the quadtree from another tree
    */
   QuadTree(const QuadTree& rhs);

   /**
    * Copies a quadtree into this tree
    */
   QuadTree& operator = (const QuadTree& rhs);

public:
  /**
   * Internal node
   */
  class Node
  {
  public:
    /**
     * Creates a new node
     */
    Node();

    /**
     * Destroys the node, freeing children
     */
    ~Node();

  private:
    // Quadtree needs access to internal,
    // but outside world doesn't 
    friend class QuadTree<T>;

    /// List of children
    Node *child[4];
    /// Pointer to parent
    Node *parent;
    /// Stored value
    T *value;
    /// Index in the parent's child array
    unsigned index;
  };

private:

};

#endif /*__ENGINE_QUADTREE_H__*/