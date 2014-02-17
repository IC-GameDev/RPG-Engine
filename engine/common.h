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
// Standard C++
# include <exception>
# include <iostream>
# include <map>
# include <sstream>
# include <vector>
// Dependencies
# include <png.h>
# include <lua.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>
# include <glm/ext.hpp>
// Engine
# include "engine/exception.h"
# include "engine/lua.h"
# include "engine/camera.h"
# include "engine/entity.h"
# include "engine/object.h"
# include "engine/building.h"
# include "engine/level.h"
# include "engine/world.h"
#else
// Standard C
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
#endif

#endif /*__ENGINE_COMMON_H__*/
