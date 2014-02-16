// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.

#include <exception>
#include <iostream>
#include <SDL2/SDL.h>
#include "engine/common.h"
#include "game/game.h"

// -----------------------------------------------------------------------------
Game::Game()
  : vp_width(800),
    vp_height(600)
{
}

// -----------------------------------------------------------------------------
void Game::Init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    EXCEPT << "Cannot init SDL: " << SDL_GetError();
  }
}

// -----------------------------------------------------------------------------
void Game::Run()
{
}

// -----------------------------------------------------------------------------
void Game::Destroy()
{
  SDL_Quit();
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
