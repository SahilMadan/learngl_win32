#include "program.hpp"

#include <Windows.h>
#include <gl/GL.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_init.hpp"

namespace {
unsigned int CompileShaderFromFile(const char* shader_path,
                                   unsigned int shader_type) {
  FILE* f = fopen(shader_path, "r");
  if (f == nullptr) {
    return 0;
  }
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  rewind(f);

  char* shader_content = (char*)malloc(fsize + 1);
  fread(shader_content, fsize, 1, f);
  shader_content[fsize] = 0;

  unsigned int shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &shader_content, nullptr);
  glCompileShader(shader);

  free(shader_content);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(shader, 512, nullptr, info_log);
    FILE* fptr = fopen("error.log", "w");
    fprintf(fptr, "Error compiling shader (%s): %s", shader_path, info_log);
    return 0;
  }
  return shader;
}
}  // namespace

unsigned int InitPipeline(const char* vertex_path, const char* fragment_path) {
  unsigned int vertex = CompileShaderFromFile(vertex_path, GL_VERTEX_SHADER);
  if (!vertex) {
    return 0;
  }
  unsigned int fragment =
      CompileShaderFromFile(fragment_path, GL_FRAGMENT_SHADER);
  if (!fragment) {
    glDeleteShader(vertex);
    return 0;
  }

  unsigned int program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);
  glLinkProgram(program);

  int success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetProgramInfoLog(program, 512, nullptr, info_log);
    FILE* fptr = fopen("error.log", "w");
    fprintf(fptr, "Error linking program: %s", info_log);
    return 0;
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return program;
}

void UsePipeline(unsigned int pipeline_program) {
  glUseProgram(pipeline_program);
}

void SetPipelineUniformBool(unsigned int pipeline_program, const char* name,
                            bool value) {
  glUniform1i(glGetUniformLocation(pipeline_program, name), (int)value);
}

void SetPipelineUniformInt(unsigned int pipeline_program, const char* name,
                           int value) {
  glUniform1i(glGetUniformLocation(pipeline_program, name), value);
}

void SetPipelineUniformFloat(unsigned int pipeline_program, const char* name,
                             float value) {
  glUniform1f(glGetUniformLocation(pipeline_program, name), value);
}