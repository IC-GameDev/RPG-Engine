// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.

#include "engine/common.h"
#include "game/common.h"

// -----------------------------------------------------------------------------
Game::Game()
  : vp_width(800),
    vp_height(600),
    window(NULL)
{
}

// -----------------------------------------------------------------------------
void Game::Init()
{
  if (glfwInit() != GL_TRUE)
    EXCEPT << "Cannot initialise GLFW";

  if (!(window = glfwCreateWindow(vp_width, vp_height, "Game", NULL, NULL)))
    EXCEPT << "Cannot create GLFW Window";

  glfwMakeContextCurrent(window);
  if (glewInit() != GLEW_OK)
    EXCEPT << "Cannot initialise GLEW";
}

// -----------------------------------------------------------------------------
void Game::Run()
{
  while (!glfwWindowShouldClose(window))
  {
    glfwGetWindowSize(window, &vp_width, &vp_height);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

// -----------------------------------------------------------------------------
void Game::Destroy()
{
  if (window != NULL)
  {
    glfwDestroyWindow(window);
    window = NULL;
  }

  glfwTerminate();
}

// -----------------------------------------------------------------------------
int main(int argc, char **argv)
{
  Game * game = NULL;

  try
  {    
    game = new Game;
    game->Init();
    game->Run();
    game->Destroy();
    delete game;

    return EXIT_SUCCESS;
  }
  catch (std::exception& e)
  {
    if (game == NULL)
    {
      delete game;
      game = NULL;
    }

    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
