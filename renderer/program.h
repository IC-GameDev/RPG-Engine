// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_SHADER_H__
#define __ENGINE_SHADER_H__

class Program
{
public:
       Program(const std::string& name_);
      ~Program();

  void Compile(const std::string& file, GLenum type);
  void Link();

  void Uniform(const std::string& name, int value);
  void Uniform(const std::string& name, const glm::ivec2& vec);
  void Uniform(const std::string& name, const glm::vec2& vec);
  void Uniform(const std::string& name, GLenum type, GLuint tex, int attr);

private:
  std::map<std::string, GLint> uniforms;
  std::string                  name;
  GLuint                       prog;
};

#endif /*__ENGINE_SHADER_H__*/
