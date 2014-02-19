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
  /**
   * Creates a new game object, initialising GLFW
   */
  Game();

  /**
   * Destroys allocated resources, terminating GLFW
   */
  ~Game();

  /**
   * Initialises the game, loading resources
   */
  void Init();

  /**
   * Main loop
   */
  void Run();

private:
  /// Size of the viewport
  glm::ivec2 viewport;
  /// Reference to the GLFW window
  GLFWwindow *window;
  /// Rendering subsystem
  Renderer *renderer;
  /// Game world
  World *world;
};

#endif /*__GAME_GAME_H__*/