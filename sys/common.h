// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_COMMON_H__
#define __ENGINE_COMMON_H__

#define _USE_MATH_DEFINES

#ifdef __cplusplus
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
# include <sstream>
# include <vector>
// Dependencies
//# include <png.h>
//# include <lua.hpp>
# include <GL/glew.h>
# define GLM_FORCE_RADIANS
# include <glm/glm.hpp>
# include <glm/ext.hpp>
// Our headers
# include "core/exception.h"
# include "core/hashmap.h"
# include "core/quadtree.h"
# include "core/lua.h"
# include "renderer/program.h"
# include "renderer/renderer.h"
# include "game/camera.h"
# include "game/entity.h"
# include "game/object.h"
# include "game/building.h"
# include "game/level.h"
# include "game/world.h"
# include "sys/engine.h"
// Platform specifics
# if defined(R_WINDOWS)
#   define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
# elif defined(R_LINUX)
#   include <X11/Xlib.h>
#   include <X11/Xatom.h>
#   include <X11/Xutil.h>
#   include <GL/glx.h>
# elif defined(R_MAC)
# else
#   error "Undefined platform"
# endif

#else
// Standard C
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
#endif

#endif /*__ENGINE_COMMON_H__*/
