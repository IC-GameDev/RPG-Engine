// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.

varying vec4 v_position;

void main()
{
  vec2 xz = v_position.xz;
  if (abs(xz.x - floor(xz.x)) < 0.1 || abs(xz.y - floor(xz.y)) < 0.1)
  {
    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
  }
  else
  {
    gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
  }
}