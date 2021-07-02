#ifdef _WIN32
#include "winGL.h"

PFNGLSHADERSOURCEPROC glShaderSource = 0;
PFNGLUNIFORM4FPROC glUniform4f = 0;
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = 0;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = 0;
PFNGLBINDBUFFERPROC glBindBuffer = 0;
PFNGLCOMPILESHADERPROC glCompileShader = 0;
PFNGLUSEPROGRAMPROC glUseProgram = 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = 0;
PFNGLGENBUFFERSPROC glGenBuffers = 0;
PFNGLCREATESHADERPROC glCreateShader = 0;
PFNGLBUFFERDATAPROC glBufferData = 0;
PFNGLDELETESHADERPROC glDeleteShader = 0;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = 0;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = 0;
PFNGLLINKPROGRAMPROC glLinkProgram = 0;
PFNGLGETPROGRAMIVPROC glGetProgramiv = 0;
PFNGLACTIVETEXTUREPROC glActiveTexture = 0;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = 0;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = 0;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = 0;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = 0;
PFNGLDELETEPROGRAMPROC glDeleteProgram = 0;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = 0;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = 0;
PFNGLATTACHSHADERPROC glAttachShader = 0;
PFNGLGETSHADERIVPROC glGetShaderiv = 0;
PFNGLUNIFORM1IPROC glUniform1i = 0;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = 0;
PFNGLCREATEPROGRAMPROC glCreateProgram = 0;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = 0;

void loadOpenGLFunctions()
{
	glShaderSource = (PFNGLSHADERSOURCEPROC)(wglGetProcAddress("glShaderSource"));
	glUniform4f = (PFNGLUNIFORM4FPROC)(wglGetProcAddress("glUniform4f"));
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)(wglGetProcAddress("wglChoosePixelFormatARB"));
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)(wglGetProcAddress("glDeleteBuffers"));
	glBindBuffer = (PFNGLBINDBUFFERPROC)(wglGetProcAddress("glBindBuffer"));
	glCompileShader = (PFNGLCOMPILESHADERPROC)(wglGetProcAddress("glCompileShader"));
	glUseProgram = (PFNGLUSEPROGRAMPROC)(wglGetProcAddress("glUseProgram"));
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)(wglGetProcAddress("glEnableVertexAttribArray"));
	glGenBuffers = (PFNGLGENBUFFERSPROC)(wglGetProcAddress("glGenBuffers"));
	glCreateShader = (PFNGLCREATESHADERPROC)(wglGetProcAddress("glCreateShader"));
	glBufferData = (PFNGLBUFFERDATAPROC)(wglGetProcAddress("glBufferData"));
	glDeleteShader = (PFNGLDELETESHADERPROC)(wglGetProcAddress("glDeleteShader"));
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)(wglGetProcAddress("glDeleteVertexArrays"));
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)(wglGetProcAddress("glVertexAttribPointer"));
	glLinkProgram = (PFNGLLINKPROGRAMPROC)(wglGetProcAddress("glLinkProgram"));
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)(wglGetProcAddress("glGetProgramiv"));
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)(wglGetProcAddress("glActiveTexture"));
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)(wglGetProcAddress("glUniformMatrix4fv"));
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)(wglGetProcAddress("glValidateProgram"));
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)(wglGetProcAddress("glGetProgramInfoLog"));
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)(wglGetProcAddress("glGetShaderInfoLog"));
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)(wglGetProcAddress("glDeleteProgram"));
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)(wglGetProcAddress("glGenVertexArrays"));
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)(wglGetProcAddress("wglCreateContextAttribsARB"));
	glAttachShader = (PFNGLATTACHSHADERPROC)(wglGetProcAddress("glAttachShader"));
	glGetShaderiv = (PFNGLGETSHADERIVPROC)(wglGetProcAddress("glGetShaderiv"));
	glUniform1i = (PFNGLUNIFORM1IPROC)(wglGetProcAddress("glUniform1i"));
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)(wglGetProcAddress("glBindVertexArray"));
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)(wglGetProcAddress("glCreateProgram"));
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)(wglGetProcAddress("glGetUniformLocation"));
}
#endif
