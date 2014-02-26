// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -----------------------------------------------------------------------------
Camera::Camera()
  : position(0.0f)
  , direction(1.0f, 0.0f, 0.0f)
  , up(0.0f, 1.0f, 0.0f)
  , fov(45.0f)
  , nearPlane(0.1f)
  , farPlane(100.0f)
  , dirty(true)
{
  Renderer::vpWidth.SetModified();
}

// -----------------------------------------------------------------------------
const glm::mat4& Camera::GetView()
{
  if (dirty)
  {
    viewMatrix = glm::lookAt(position, position + direction, up);
  }

  return viewMatrix;
}

// -----------------------------------------------------------------------------
const glm::mat4& Camera::GetProj()
{
  if (dirty || Renderer::vpReload.IsModified())
  {
    aspect = Renderer::vpWidth.GetFloat() / Renderer::vpHeight.GetFloat();
    projMatrix = glm::perspective(fov, aspect, nearPlane, farPlane);
  }

  return projMatrix;
}
