// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __SYS_COMMON_H__
#define __SYS_COMMON_H__

#define _USE_MATH_DEFINES
#define GLM_FORCE_RADIANS

// Standard C
# include <cmath>
# include <cstdio>
# include <cstdlib>
# include <ctime>
// Standard C++
# include <exception>
# include <iostream>
# include <map>
# include <set>
# include <queue>
# include <sstream>
# include <vector>
// Dependencies
# include <lua.hpp>
# include <GL/glew.h>
# include <glm/glm.hpp>
# include <glm/ext.hpp>
// Our headers
# include "core/concurrent.h"
# include "core/exception.h"
# include "core/hashmap.h"
# include "core/quadtree.h"
# include "core/queue.h"
# include "core/lua.h"
# include "sys/cvar.h"
# include "sys/event.h"
# include "sys/threads.h"
# include "sys/engine.h"
# include "sys/network.h"
# include "renderer/buffer.h"
# include "renderer/meshmngr.h"
# include "renderer/program.h"
# include "renderer/renderer.h"
# include "game/camera.h"
# include "game/entity.h"
# include "game/object.h"
# include "game/building.h"
# include "game/level.h"
# include "game/world.h"
// Platform specifics
# if defined(R_WINDOWS)
#   define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
# elif defined(R_LINUX)
#   include <X11/Xlib.h>
#   include <X11/Xatom.h>
#   include <X11/Xutil.h>
#   include <X11/extensions/xf86vmode.h>
#   include <GL/glx.h>
#   include <unistd.h>
#   include <pthread.h>
#   include <errno.h>
# elif defined(R_MAC)
# else
#   error "Undefined platform"
# endif

#endif /*__ENGINE_COMMON_H__*/
