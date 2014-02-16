// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.

#ifndef __GAME_GAME_H__
#define __GAME_GAME_H__

/**
 * Main game class
 */
class Game
{
public:
  Game();
  virtual ~Game() { Destroy(); }

  void Init();
  void Run();
  void Destroy();

private:
  int vp_width;
  int vp_height;
};

#endif /*__GAME_GAME_H__*/