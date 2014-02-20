

uniform mat4 u_proj;
uniform mat4 u_view;

void main()
{
  gl_Position = u_proj * u_view * gl_Vertex;
}