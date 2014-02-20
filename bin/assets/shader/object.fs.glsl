uniform sampler2D u_texture;


void main()
{
  gl_FragColor = texture2D(u_texture, vec2(0.0, 0.0));
}