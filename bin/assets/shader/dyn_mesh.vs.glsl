// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
uniform mat4 u_proj;
uniform mat4 u_view;

varying vec4 v_position;

void main()
{
  v_position = gl_Vertex;
  gl_Position = u_proj * u_view * v_position;
}
