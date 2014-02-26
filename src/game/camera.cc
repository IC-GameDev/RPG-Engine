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
    Compute();
    dirty = false;
  }

  return viewMatrix;
}

// -----------------------------------------------------------------------------
const glm::mat4& Camera::GetProj()
{
  if (dirty || Renderer::vpReload.IsModified())
  {
    Compute();
    dirty = false;
  }

  return projMatrix;
}

// -----------------------------------------------------------------------------
void Camera::Compute()
{
  viewMatrix = glm::lookAt(position, position + direction, up);
  aspect = Renderer::vpWidth.GetFloat() / Renderer::vpHeight.GetFloat();
  projMatrix = glm::perspective(fov, aspect, nearPlane, farPlane);
}

// -----------------------------------------------------------------------------
CameraTopDown::CameraTopDown()
  : center(0.0f)
  , offset(10.0f, 10.0f, 10.0f)
  , speed(0.00001f)
{

}

// -----------------------------------------------------------------------------
void CameraTopDown::Move(const Direction& dir, bool start)
{
  moveDir = start ? (moveDir | dir) : (moveDir & (~dir));
}

// -----------------------------------------------------------------------------
void CameraTopDown::Update(float delta)
{
  glm::vec3 move(0.0f);

  // Cumulate move directions
  if (moveDir & UP)
  {
    move += glm::vec3(1.0f, 0.0f, 1.0f);
  }
  if (moveDir & DOWN)
  {
    move -= glm::vec3(1.0f, 0.0f, 1.0f);
  }
  if (moveDir & RIGHT)
  {
    move += glm::vec3(-1.0f, 0.0f, 1.0f);
  }
  if (moveDir & LEFT)
  {
    move -= glm::vec3(-1.0f, 0.0f, 1.0f);
  }

  // Normalize & multiply with speed
  if (glm::length(move) > 0.01f)
  {
    center += glm::normalize(move) * delta * speed;
  }

  dirty = true;
  position = center + offset;
  direction = glm::normalize(-offset);
}
