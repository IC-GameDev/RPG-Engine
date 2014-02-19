// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_SHADER_H__
#define __ENGINE_SHADER_H__

class Shader
{
public:
  /**
   * Creates a new shader
   * @param name Unique identifier
   */
  Shader(const std::string& name_);

  /**
   * Destroys a shader
   */
  ~Shader();

  /**
   * Compiles a source file
   * @param file Path to the shader source
   * @param type Type of the shader (vertex or fragment)
   */
  void Compile(const std::string& file, GLenum type);

  /**
   * Links a shader
   */
  void Link();

  /**
   * Sets the value of an integer uniform
   * @param name Uniform name
   * @param value New value
   */
  void Uniform(const std::string& name, int value);

  /**
   * Sets the value of a 2D vector
   * @param name Uniform name
   * @param value New value
   */
  void Uniform(const std::string& name, const glm::ivec2& vec);

  /**
   * Sets the value of a 2D vector
   * @param name Uniform name
   * @param value New value
   */
  void Uniform(const std::string& name, const glm::vec2& vec);

  /**
   * Binds a texture
   * @param name Uniform name
   * @param type Texture type
   * @param tex Texture object
   * @param attr Bind Point
   */
  void Uniform(const std::string& name, GLenum type, GLuint tex, int attr);

private:
  /// Cached uniform locations
  std::map<std::string, GLint> uniforms;
  /// Shader program name
  std::string name;
  /// Program object
  GLuint prog;
};

#endif /*__ENGINE_SHADER_H__*/
