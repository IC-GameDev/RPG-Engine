// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_HASHMAP_H__
#define __ENGINE_HASHMAP_H__

/// 64 bit hash type
typedef unsigned long long Hash;

/**
 * Please specialise this for individual types
 */
template <class T>
inline Hash Encode(const T& value)
{
  return (Hash)&value;
}

/**
 * Integer 2D vector hash
 */
template <>
inline Hash Encode<glm::ivec2>(const glm::ivec2& value)
{
  Hash hash;

  hash = 0ull;
  hash += (value.x + 0x7fffffffull) << 32ull;
  hash += (value.y + 0x7fffffffull) <<  0ull;

  return hash;
}

/**
 * Chained scatter table with Bren't variation
 */
template <class Key, class Value, Hash Encode(const Key&) = Encode >
class HashMap
{
public:
  /**
   * Initialises an empty hashmap
   */
  HashMap()
    : capacity(0)
    , size(0)
    , data(NULL)
  {
  }

  /**
   * Frees allocated memory
   */
  ~HashMap()
  {
    Clear();
  }

  /**
   * Inserts a new element into the hashmap
   */
  void Insert(const Key& key, const Value& value)
  {

  }

  /**
   * Removes an element from the hashmap
   */
  void Remove(const Key& key)
  {

  }

  /**
   * Retrieves an element from the hashmap
   */
  const Value& Find(const Key& key)
  {
    return *((Value*)NULL);
  }

  /**
   * Checks whether the hashmap contains a give key
   */
  bool Contains(const Key& key)
  {
    return false;
  }

  /**
   * Clears the contents
   */
  void Clear()
  {

  }

  /**
   * Returns the number of elements actually present in the hash map
   */
  size_t GetSize()
  {
    return size;
  }

  /**
   * returns the capacity of the hash map
   */
  size_t GetCapacity()
  {
    return capacity;
  }

private:
  /// Number of elements which can be stored in the hashmap
  size_t capacity;
  /// Size of the hashmap
  size_t size;
  /// Storage
  Value *data;
};

#endif
