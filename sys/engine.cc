// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -------------------------------------------------------------------------------------------------
CVar Engine::wndWidth("wndWidth", CVAR_INT | CVAR_CONFIG, "800", "Width of the window");
CVar Engine::wndHeight("wndHeight", CVAR_INT | CVAR_CONFIG, "600", "Height of the window");
CVar Engine::wndTitle("wndTitle", CVAR_STRING | CVAR_CONFIG, "Valkyrie", "Title of the window");
CVar Engine::wndReload("wndReload", CVAR_BOOL, "true", "Flag to reload the window");
// ---------------------------------------------------------------------------------------------------------------------