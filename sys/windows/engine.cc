// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -----------------------------------------------------------------------------
static const char *wndTypePool[] = { "windowed", "fullscreen", "windowed_fs" };
CVar Engine::wndType("wndType", CVAR_INT | CVAR_CONFIG, "windowed", wndTypePool, "Window type");

// -----------------------------------------------------------------------------
// Windows implementation of platform-specific features
// -----------------------------------------------------------------------------
class EngineImpl : public Engine
{
public:
           EngineImpl();

  void     Init();
  void     Run();
  void     Destroy();

private:
  static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

  void     InitWindow();
  void     UpdateWindow();
  void     DestroyWindow();

  HINSTANCE   inst;
  HWND        window;
  HDC         device;
  HGLRC       context;
  bool        fullscreen;
};

// -----------------------------------------------------------------------------
static EngineImpl engineImpl;
Engine *engine = &engineImpl;

// -----------------------------------------------------------------------------
LRESULT CALLBACK EngineImpl::WndProc(HWND handle, UINT msg,
                                     WPARAM wp, LPARAM lp)
{
  EngineImpl * e;
  if (msg == WM_CREATE)
  {
    if (!(e = (EngineImpl*)((LPCREATESTRUCT)lp)->lpCreateParams))
    {
      return DefWindowProc(handle, msg, wp, lp);
    }

    SetWindowLongPtr(handle, GWLP_USERDATA, (LONG)e);
  }
  else if (!(e = (EngineImpl*)GetWindowLongPtr(handle, GWLP_USERDATA)))
  {
    return DefWindowProc(handle, msg, wp, lp);
  }

  switch (msg)
  {
    case WM_KEYDOWN:
    case WM_CLOSE:
    {
      e->Quit();
      return 0;
    }
  }

  return DefWindowProc(handle, msg, wp, lp);
}

// -----------------------------------------------------------------------------
EngineImpl::EngineImpl()
  : inst(GetModuleHandle(NULL))
  , window(NULL)
  , device(NULL)
  , context(NULL)
  , fullscreen(false)
{
}


// -----------------------------------------------------------------------------
void EngineImpl::Init()
{
  InitWindow();
  renderer->Init();
}

// -----------------------------------------------------------------------------
void EngineImpl::Destroy()
{
  renderer->Destroy();
  DestroyWindow();
}

// -----------------------------------------------------------------------------
void EngineImpl::InitWindow()
{
  PIXELFORMATDESCRIPTOR pfd;
  UINT formatCount;
  WNDCLASSEX wc;
  int pixelFormat;

  // Register the class
  if (!GetClassInfoEx(inst, "engine", &wc))
  {
    memset(&wc, 0, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = inst;
    wc.hIcon = LoadIcon(inst, MAKEINTRESOURCE(ID_ICON_ENGINE));
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "engine";

    if (!RegisterClassEx(&wc))
    {
      EXCEPT << "Cannot register window class";
    }
  }

  // Create the actual window
  if (!(window = CreateWindowEx(0, "vkEngine", "", WS_SYSMENU,
                                0, 0, 0, 0, 0, 0, inst, this)))
  {
    EXCEPT << "Cannot create window";
  }

  if (!(device = GetDC(window)))
  {
    EXCEPT << "Cannot retrieve device context";
  }

  // Initialise the OpenGL context
  memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.iLayerType = PFD_MAIN_PLANE;

  if (!(dummyFormat = ChoosePixelFormat(device, &pfd)))
  {
    EXCEPT << "[Engine] Cannot choose pixel format";
  }

  if (!SetPixelFormat(device, dummyFormat, &pfd))
  {
    EXCEPT << "[Engine] Cannot set pixel format";
  }

  if (!(context = wglCreateContext(device)))
  {
    EXCEPT << "[Engine] Cannot create dummy context";
  }

  wglMakeCurrent(device, context);
  if (glewInit() != GLEW_OKAY)
  {
    EXCEPT << "[Engine] Cannot link GL extensions";
  }
  wglMakeCurrent(NULL, NULL);
}

// -----------------------------------------------------------------------------
void EngineImpl::DestroyWindow()
{
  WNDCLASSEX wc;

  if (context)
  {
      wglMakeCurrent(NULL, NULL);
      wglDeleteContext(context);
      context = NULL;
  }

  if (device)
  {
      ReleaseDC(window, device);
      device = NULL;
  }

  if (window)
  {
    if (fullscreen)
    {
      ChangeDisplaySettings(NULL, 0);
    }

    ShowWindow(window, SW_HIDE);
    CloseWindow(window);
    DestroyWindow(window);
    window = NULL;
  }

  if (GetClassInfoEx(inst, "engine", &wc))
  {
    UnregisterClass("engine", inst);
  }
}

// -----------------------------------------------------------------------------
void EngineImpl::UpdateWindow()
{
  DWORD style, exStyle;
  RECT r;

  switch (wndType.GetInt())
  {
    // Windowed mode
    case 0:
    {
      r.left = (GetSystemMetrics(SM_CXSCREEN) - wndWidth.GetInt()) >> 1;
      r.top = (GetSystemMetrics(SM_CYSCREEN) - wndHeight.GetInt()) >> 1;
      r.right = r.left + wndWidth.GetInt();
      r.bottom =  r.top + wndHeight.GetInt();

      exStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
      style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

      fullscreen = false;
      ChangeDisplaySettings(NULL, 0);
      break;
    }
    // Windowed fullscreen
    case 1:
    {
      MONITORINFO mm;
      HMONITOR hmm;

      hmm = MonitorFromWindow(window,  MONITOR_DEFAULTTONEAREST);
      mm.cbSize = sizeof(MONITORINFO);

      if (!GetMonitorInfo(hmm, &mm))
      {
        r.left   = 0;
        r.top    = 0;
        r.right  = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        r.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN);
      }
      else
      {
        r = mm.rcMonitor;
      }

      exStyle = WS_EX_APPWINDOW;
      style = WS_POPUP | WS_VISIBLE;

      fullscreen = false;
      ChangeDisplaySettings(NULL, 0);
      break;
    }
    // Fullscreen
    case 2:
    {
      DEVMODE ss;

      r.left = 0;
      r.top = 0;
      r.right = wndWidth.GetInt();
      r.bottom = wndHeight.GetInt();

      exStyle = WS_EX_APPWINDOW;
      style = WS_POPUP;

      fullscreen = true;
      EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &ss);
      ss.dmPelsWidth  = wndWidth.GetInt();
      ss.dmPelsHeight = wndHeight.GetInt();
      ss.dmBitsPerPel = 32;
      ss.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

      if (ChangeDisplaySettings(&ss, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
      {
        throw vkException("[Engine] Cannot switch to fullscreen");
      }
      break;
    }
  }

  AdjustWindowRectEx(&r, style, FALSE, exStyle);

  SetWindowLongPtr(window, GWL_STYLE, style);
  SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
  SetWindowText(window, wndTitle.GetString());
  SetWindowPos(window, NULL, r.left, r.top,
               r.right - r.left, r.bottom - r.top,
               SWP_SHOWWINDOW);
}

// -----------------------------------------------------------------------------
void EngineImpl::Run()
{
  MSG msg;

  running = true;
  while (running)
  {
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (wndReload.GetBool())
    {
      UpdateWindow();
      wndReload.SetBool(false);
    }

    renderer->Frame();
    SwapBuffers(device);
  }
}

// -----------------------------------------------------------------------------
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
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
