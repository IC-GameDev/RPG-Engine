// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_WORLD_H__
#define __ENGINE_WORLD_H__

class World
{
public:
  virtual void Load(const std::string& script) = 0;
  virtual void Unload() = 0;
};

extern World *world;

#endif /*__ENGINE_WORLD_H__*/
