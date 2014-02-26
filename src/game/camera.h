// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_CAMERA_H__
#define __ENGINE_CAMERA_H__

// -----------------------------------------------------------------------------
// Camera state
// -----------------------------------------------------------------------------
class Camera
{
public:
                      Camera();
  virtual            ~Camera() { }

  const glm::mat4&    GetView();
  const glm::mat4&    GetProj();

protected:
  virtual void        Compute();

  glm::vec3           position;
  glm::vec3           direction;
  glm::vec3           up;
  float               fov;
  float               nearPlane;
  float               farPlane;

  mutable bool        dirty;
  mutable float       aspect;
  mutable glm::mat4   viewMatrix;
  mutable glm::mat4   projMatrix;
};

// -----------------------------------------------------------------------------
// Top down camera controlled by keyboard
// -----------------------------------------------------------------------------
class CameraTopDown : public Camera
{
public:
  enum Direction
  {
    UP    = (1 << 0),
    DOWN  = (1 << 1),
    LEFT  = (1 << 2),
    RIGHT = (1 << 3)
  };

                CameraTopDown();
  void          Move(const Direction& dir, bool start);
  void          Update(float delta);

public:
  long          moveDir;
  glm::vec3     center;
  glm::vec3     offset;
  float         speed;
};

// -----------------------------------------------------------------------------
// Camera which follows an in-game entity
// -----------------------------------------------------------------------------
class CameraFollower
{

};

#endif /*__ENGINE_CAMERA_H__*/