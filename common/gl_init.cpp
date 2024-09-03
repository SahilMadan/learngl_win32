#include "gl_init.hpp"

PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM4FPROC glUniform4f;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsArb;

void InitGlFunctions() {
  glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
  glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
  glBindVertexArray =
      (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
  glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
  glCompileShader =
      (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
  glCreateProgram =
      (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
  glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
  glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
  glEnableVertexAttribArray =
      (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress(
          "glEnableVertexAttribArray");
  glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
  glGenVertexArrays =
      (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
  glGetProgramInfoLog =
      (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
  glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
  glGetShaderInfoLog =
      (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
  glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
  glGetUniformLocation =
      (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
  glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
  glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
  glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
  glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
  glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
  glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
  glVertexAttribPointer =
      (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
  wglCreateContextAttribsArb =
      (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress(
          "wglCreateContextAttribsARB");
}