// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.

#include "engine/common.h"
#include "game/common.h"

// -----------------------------------------------------------------------------
Game::Game()
  : viewport(800, 600),
    window(NULL),
    renderer(NULL),
    world(NULL)
{
}

// -----------------------------------------------------------------------------
Game::~Game()
{
  if (world)
  {
    delete world;
    world = NULL;
  }

  if (renderer)
  {
    delete renderer;
    renderer = NULL;
  }

  if (window != NULL)
  {
    glfwDestroyWindow(window);
    window = NULL;
  }

  glfwTerminate();
}

// -----------------------------------------------------------------------------
void Game::Init()
{
  // Initialise GLFW
  if (glfwInit() != GL_TRUE)
  {
    EXCEPT << "Cannot initialise GLFW";
  }

  if (!(window = glfwCreateWindow(viewport.x, viewport.y, "Game", NULL, NULL)))
  {
    glfwTerminate();
    EXCEPT << "Cannot create GLFW Window";
  }

  glfwMakeContextCurrent(window);
  if (glewInit() != GLEW_OK)
  {
    glfwDestroyWindow(window);
    glfwTerminate();
    EXCEPT << "Cannot initialise GLEW";    
  }

  // Initialises the renderer
  renderer = new Renderer();
  renderer->Init();

  // Initialises the world
  world = new World();
  world->Init();
}

// -----------------------------------------------------------------------------
void Game::Run()
{
  while (!glfwWindowShouldClose(window))
  {
    glfwGetWindowSize(window, &viewport.x, &viewport.y);
    
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
    Game game;
    game.Init();
    game.Run();
    
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
