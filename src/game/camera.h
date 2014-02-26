// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_CAMERA_H__
#define __ENGINE_CAMERA_H__

class Camera
{
public:
           Camera();
  virtual ~Camera() { }

  const glm::mat4&    GetView();
  const glm::mat4&    GetProj();

private:
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

#endif /*__ENGINE_CAMERA_H__*/