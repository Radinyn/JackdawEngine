#pragma once
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#undef near
#undef far
#include <gl/gl.h>
#include "gl/glext.h"
#include "gl/wglext.h"

extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLUNIFORM4FPROC glUniform4f;
extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

void loadOpenGLFunctions();
#endif
