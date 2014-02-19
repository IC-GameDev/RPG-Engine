// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// Linux implementation of platform-specific things
class WindowsEngine : public Engine
{
public:
           WindowsEngine();
          ~WindowsEngine();

  void     Init();
  void     Run();
  void     Destroy();

private:
  void     InitWindow();
  void     DestroyWindow();
};

// Engine instance
static WindowsEngine engineImpl;
Engine *engine = &engineImpl;

// -----------------------------------------------------------------------------
WindowsEngine::WindowsEngine()
  : dpy(NULL)
  , wnd(0)
  , wndClose(0)
  , context(NULL)
  , colormap(0)
{
}

// -----------------------------------------------------------------------------
WindowsEngine::~WindowsEngine()
{

}

// -----------------------------------------------------------------------------
void WindowsEngine::Init()
{
  InitWindow();
  renderer->Init();
}

// -----------------------------------------------------------------------------
void WindowsEngine::Run()
{
}

// -----------------------------------------------------------------------------
void WindowsEngine::Destroy()
{
  renderer->Destroy();
  DestroyWindow();
}

// -----------------------------------------------------------------------------
void WindowsEngine::InitWindow()
{
}

// -----------------------------------------------------------------------------
void WindowsEngine::DestroyWindow()
{
}

// -----------------------------------------------------------------------------
int main(int argc, char **argv)
{
  try
  {
    engine->Init();
    engine->Run();
    engine->Destroy();
    return EXIT_SUCCESS;
  }
  catch (std::exception& e)
  {
    engine->Destroy();
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
