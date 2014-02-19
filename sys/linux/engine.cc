// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -------------------------------------------------------------------------------------------------
static const char *wndTypePool[] = { "windowed", "windowed_fs", "fullscreen", NULL };
CVar Engine::wndType("wndType", CVAR_INT | CVAR_CONFIG, "windowed_fs", wndTypePool, "Window type");

// -------------------------------------------------------------------------------------------------
// Linux implementation of platform-specific things
// -------------------------------------------------------------------------------------------------
class EngineImpl : public Engine
{
public:
            EngineImpl();

  void      Init();
  void      Run();
  void      Destroy();
  uint64_t  GetTime();

private:
  void      InitWindow();
  void      UpdateWindow();
  void      DestroyWindow();

  void      InitLua();
  void      DestroyLua();

  Display   *dpy;
  Window     wnd;
  Atom       wndClose;
  GLXContext context;
  Colormap   colormap;
  int        type;
  int        x;
  int        y;
  int        width;
  int        height;
};

// Engine instance
static EngineImpl engineImpl;
Engine *engine = &engineImpl;

// -------------------------------------------------------------------------------------------------
EngineImpl::EngineImpl()
  : dpy(NULL)
  , wnd(0)
  , wndClose(0)
  , context(NULL)
  , colormap(0)
{
}

// -------------------------------------------------------------------------------------------------
void EngineImpl::Init()
{
  InitLua();
  InitWindow();
  renderer->Init();
  world->Load("assets/scripts/test.lua");
}

// -------------------------------------------------------------------------------------------------
void EngineImpl::Destroy()
{
  world->Unload();
  renderer->Destroy();
  DestroyWindow();
  DestroyLua();
}

// -------------------------------------------------------------------------------------------------
void EngineImpl::InitWindow()
{
  // Open the X display
  Window root;
  if (!(dpy = XOpenDisplay(0)) || !(root = DefaultRootWindow(dpy)))
  {
    EXCEPT << "Cannot open display";
  }

  // Check GLX version
  int min, maj;
  if (!glXQueryVersion(dpy, &maj, &min) || (maj == 1 && min < 3) || maj < 1)
  {
    EXCEPT << "Invalid GLX version (" << maj << "." << min << " < 1.3)";
  }

  // Retrieve visual info
  static int ATTR[] =
  {
    GLX_RGBA,
    GLX_RED_SIZE,       8,
    GLX_GREEN_SIZE,     8,
    GLX_BLUE_SIZE,      8,
    GLX_DOUBLEBUFFER,   2,
    None
  };

  XVisualInfo *vi;
  if (!(vi = glXChooseVisual(dpy, 0, ATTR)))
  {
    EXCEPT << "Cannot choose visual";
  }

  // Create colormap
  if (!(colormap = XCreateColormap(dpy, root, vi->visual, AllocNone)))
  {
    XFree(vi);
    EXCEPT << "Cannot create colormap";
  }

  // Create the window
  XSetWindowAttributes swa;
  swa.colormap = colormap;
  swa.border_pixel = 0;
  swa.override_redirect = True;
  swa.event_mask = StructureNotifyMask | ExposureMask |
                   KeyPressMask | ResizeRedirectMask;
  if (!(wnd = XCreateWindow(dpy, root, 0, 0, 1, 1,
                            0, vi->depth, InputOutput, vi->visual,
                            CWColormap | CWEventMask | CWColormap, &swa)))
  {
    EXCEPT << "Cannot create X window";
  }

  // Catch window close events
  wndClose = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(dpy, wnd, &wndClose, 1);

  // Make this window a popup
  Atom atom;
  if ((atom = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DIALOG", True)) != 0)
  {
    XChangeProperty(dpy, wnd, XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", True),
                    XA_ATOM, 32, PropModeReplace, (uint8_t*)&atom, 1);
  }

  // Map the window
  XEvent evt;
  XStoreName(dpy, wnd, wndTitle.GetString().c_str());
  XMapWindow(dpy, wnd);
  XSync(dpy, False);
  do
  {
    XNextEvent(dpy, &evt);
  } while (evt.type != MapNotify);

  // Create the OpenGL context
  context = glXCreateContext(dpy, vi, NULL, GL_TRUE);
  XFree(vi);
  if (!context)
  {
    EXCEPT << "Cannot create OpenGL context";
  }

  // Initialise GLEW
  glXMakeCurrent(dpy, wnd, context);
  if (glewInit() != GLEW_OK)
  {
    EXCEPT << "Cannot initialise GLEW";
  }
}

// -------------------------------------------------------------------------------------------------
void EngineImpl::DestroyWindow()
{
  if (context)
  {
    glXMakeCurrent(dpy, 0, 0);
    glXDestroyContext(dpy, context);
    context = NULL;
  }

  if (wnd)
  {
    XDestroyWindow(dpy, wnd);
    wnd = 0;
  }

  if (colormap)
  {
    XFreeColormap(dpy, colormap);
    colormap = 0;
  }

  if (dpy)
  {
    XCloseDisplay(dpy);
    dpy = NULL;
  }
}

// -------------------------------------------------------------------------------------------------
void EngineImpl::UpdateWindow()
{
  switch (type = wndType.GetInt())
  {
    // Windowed
    case 0:
    {
      XWindowAttributes attr;
      XGetWindowAttributes(dpy, DefaultRootWindow(dpy), &attr);
      x = attr.x + ((attr.width - wndWidth.GetInt()) >> 1);
      y = attr.y + ((attr.height - wndHeight.GetInt()) >> 1);
      width = wndWidth.GetInt();
      height = wndHeight.GetInt();
      break;
    }
    // Windowed fullscreen
    case 1:
    {
      XWindowAttributes attr;
      XGetWindowAttributes(dpy, DefaultRootWindow(dpy), &attr);
      x = attr.x;
      y = attr.y;
      width = attr.width;
      height = attr.height;
      break;
    }
    // Fullscreen
    case 2:
    {
      break;
    }
  }

  XMoveResizeWindow(dpy, wnd, x, y, width, height);
}

// -------------------------------------------------------------------------------------------------
void EngineImpl::Run()
{
  XEvent evt;

  running = true;
  while (running)
  {
    while (XPending(dpy) > 0)
    {
      XNextEvent(dpy, &evt);
      switch (evt.type)
      {
        case ResizeRequest:
        {
          switch (type)
          {
            case 0:
            {
              XResizeWindow(dpy, wnd, width, height);
              break;
            }
            case 1:
            {
              XMoveResizeWindow(dpy, wnd, x, y, width, height);
              break;
            }
            case 2:
            {
              break;
            }
          }

          break;
        }
        case ClientMessage:
        {
          if (evt.xclient.data.l[0] == (int)wndClose)
          {
            running = false;
            break;
          }

          break;
        }
      }
    }

    if (wndReload.GetBool())
    {
      UpdateWindow();
      wndReload.SetBool(false);
    }

    renderer->Frame();
    glXSwapBuffers(dpy, wnd);
  }
}

// -------------------------------------------------------------------------------------------------
uint64_t EngineImpl::GetTime()
{
  struct timespec tv;
  clock_gettime(CLOCK_REALTIME, &tv);
  return (uint64_t)tv.tv_sec * 1000000000ull + (uint64_t)tv.tv_nsec;
}

// -------------------------------------------------------------------------------------------------
void EngineImpl::InitLua()
{

}

// -------------------------------------------------------------------------------------------------
void EngineImpl::DestroyLua()
{

}

// -------------------------------------------------------------------------------------------------
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
