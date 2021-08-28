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

extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLUNIFORM3UIPROC glUniform3ui;
extern PFNGLUNIFORM3FPROC glUniform3f;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLUNIFORM2IPROC glUniform2i;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLUNIFORM1UIPROC glUniform1ui;
extern PFNGLUNIFORM2FPROC glUniform2f;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLUNIFORM4IPROC glUniform4i;
extern PFNGLUNIFORM2UIPROC glUniform2ui;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM3IPROC glUniform3i;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLUNIFORM4UIPROC glUniform4ui;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLUNIFORM4FPROC glUniform4f;
extern PFNGLCOMPILESHADERPROC glCompileShader;

void loadOpenGLFunctions();
#endif
