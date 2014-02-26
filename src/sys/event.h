// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __SYS_INPUT_H__
#define __SYS_INPUT_H__

// -----------------------------------------------------------------------------
// Input event constants
// -----------------------------------------------------------------------------
enum EventType
{
  EVT_MOUSE,
  EVT_KEYBOARD,
  EVT_NETWORK
};

enum MouseButton
{
  BTN_LEFT   = 1,
  BTN_MDL    = 2,
  BTN_RIGHT  = 4
};

enum KeyButton
{
  // Numeric keys
  KEY_ESC   = 0,
  KEY_SHIFT = 1,
  KEY_CTRL  = 2,
  KEY_SPACE = 3,
  KEY_ENTER = 4,

  // Letters
  KEY_A     = 'A',
  KEY_W     = 'W',
  KEY_S     = 'S',
  KEY_D     = 'D',

  // Undefined
  KEY_UNDEF = 0x7fffffff
};

// -----------------------------------------------------------------------------
// Various event objects
// -----------------------------------------------------------------------------
struct KeyboardEvent
{
  KeyButton key;
  bool      state;
};

struct MouseEvent
{
  MouseButton button;
  int         mouseX;
  int         mouseY;
  bool        state;
};

struct NetworkEvent
{

};

// -----------------------------------------------------------------------------
// Event object dispatched by the system to the game logic thread
// -----------------------------------------------------------------------------
struct InputEvent
{
  EventType type;
  union
  {
    KeyboardEvent   keyboard;
    MouseEvent      mouse;
    NetworkEvent    network;
  };
};

#endif
