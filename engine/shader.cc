// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "engine/common.h"


// -----------------------------------------------------------------------------
Shader::Shader(const std::string& name_)
  : name(name_)
  , prog(0)
{
}

// -----------------------------------------------------------------------------
Shader::~Shader()
{
  if (prog)
  {
    std::vector<GLuint> shaders;
    GLint count;

    glGetProgramiv(prog, GL_ATTACHED_SHADERS, &count);
    if (count > 0)
    {
      shaders.resize(count);
      glGetAttachedShaders(prog, count, NULL, &shaders[0]);
      for (size_t i = 0; i < count; ++i)
      {
        glDetachShader(prog, shaders[i]);
        glDeleteShader(shaders[i]);
      }
    }

    glDeleteProgram(prog);
    prog = 0;
  }
}

// -----------------------------------------------------------------------------
void Shader::Compile(const std::string& file, GLenum type)
{
  GLuint shader;
  std::string buffer;
  size_t length;
  GLint flag;
  FILE *fin;
  const char *ptr;

  // Read the source file
  if (!(fin = fopen(file.c_str(), "rb")))
  {
    EXCEPT << "Cannot open file '" << file << "'";
  }

  fseek(fin, 0, SEEK_END);
  length = ftell(fin);
  fseek(fin, 0, SEEK_SET);

  buffer.resize(length + 1);
  buffer[length] = '\0';
  if (fread(&buffer[0], sizeof(char), length, fin) != length)
  {
    fclose(fin);
    EXCEPT << "Cannot read file '" << file << "'";
  }
  fclose(fin);

  // Compile the shader
  if (!(shader = glCreateShader(type)))
  {
    EXCEPT << "Cannot create shader object";
  }

  ptr = &buffer[0];
  glShaderSource(shader, 1, &ptr, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &flag);
  if (flag != GL_TRUE)
  {
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &flag);
    if (flag > 0)
    {
      buffer.resize(flag + 1);
      buffer[flag] = '\0';
      glGetShaderInfoLog(shader, flag, NULL, &buffer[0]);
    }
    else
    {
      buffer = "No info";
    }

    EXCEPT << "Cannot compile '" << file << "':\n" << buffer;
  }

  // Attach the shader
  prog = prog ? prog : glCreateProgram();
  glAttachShader(prog, shader);
}

// -----------------------------------------------------------------------------
void Shader::Link()
{
  GLint flag, length;
  std::string buffer;
  std::string name;
  
  // List of attributes & locations
  struct 
  {
    const char *name;
    GLuint loc;
  } 
  attribs[] =
  {
    { "in_vertex", 0 },
    { "in_uv",     1 }
  };

  // If shader is empty, throw an error
  if (!prog)
  {
    EXCEPT << "No shaders attached";
  }

  // Set attribute locations
  for (size_t i = 0; i < sizeof(attribs) / sizeof(attribs[0]); ++i)
  {
    glBindAttribLocation(prog, attribs[i].loc, attribs[i].name);
  }

  // Try to link
  glLinkProgram(prog);
  glGetProgramiv(prog, GL_LINK_STATUS, &flag);
  if (flag != GL_TRUE)
  {
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &flag);
    if (flag > 0)
    {
      buffer.resize(flag + 1);
      buffer[flag] = '\0';
      glGetProgramInfoLog(prog, flag, NULL, &buffer[0]);
    }
    else
    {
      buffer = "No info";
    }

    EXCEPT << "Cannot link '" << name << "':\n" << buffer;
  }

  // Retrieve uniform locations
  glGetProgramiv(prog, GL_ACTIVE_UNIFORMS, &flag);
  glGetProgramiv(prog, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
  for (GLint i = 0; i < flag; ++i)
  {
    GLenum type;
    GLint size;
    buffer.resize(length + 1);
    glGetActiveUniform(prog, i, length, NULL, &size, &type, &buffer[0]);
    while (!buffer.empty() && *buffer.rbegin() ==  '\0')
    {
      buffer.erase(buffer.end() - 1);
    }

    uniforms[buffer] = glGetUniformLocation(prog, buffer.c_str());
  }
}

// -----------------------------------------------------------------------------
void Shader::Uniform(const std::string& name, int value)
{
  std::map<std::string, GLint>::iterator it;

  if ((it = uniforms.find(name)) == uniforms.end()) 
  {
    return;
  }

  glUniform1i(it->second, value);
}

// -----------------------------------------------------------------------------
void Shader::Uniform(const std::string& name, const glm::ivec2& vec)
{
  std::map<std::string, GLint>::iterator it;

  if ((it = uniforms.find(name)) == uniforms.end()) 
  {
    return;
  }

  glUniform2iv(it->second, 1, glm::value_ptr(vec));
}

// -----------------------------------------------------------------------------
void Shader::Uniform(const std::string& name, const glm::vec2& vec)
{
  std::map<std::string, GLint>::iterator it;

  if ((it = uniforms.find(name)) == uniforms.end()) 
  {
    return;
  }

  glUniform2fv(it->second, 1, glm::value_ptr(vec));
}

// -----------------------------------------------------------------------------
void Shader::Uniform(const std::string& name, GLenum type, GLuint tex, int attr)
{
  std::map<std::string, GLint>::iterator it;

  if ((it = uniforms.find(name)) == uniforms.end()) 
  {
    return;
  }

  glActiveTexture(GL_TEXTURE + attr);
  glBindTexture(type, tex);
  glUniform1i(it->second, attr);
}
