#ifdef _WIN32
#include "winGL.h"

PFNGLDELETEPROGRAMPROC glDeleteProgram = 0;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = 0;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = 0;
PFNGLGENBUFFERSPROC glGenBuffers = 0;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = 0;
PFNGLGETPROGRAMIVPROC glGetProgramiv = 0;
PFNGLUNIFORM3UIPROC glUniform3ui = 0;
PFNGLUNIFORM3FPROC glUniform3f = 0;
PFNGLGETSHADERIVPROC glGetShaderiv = 0;
PFNGLUNIFORM2IPROC glUniform2i = 0;
PFNGLSHADERSOURCEPROC glShaderSource = 0;
PFNGLUNIFORM1UIPROC glUniform1ui = 0;
PFNGLUNIFORM2FPROC glUniform2f = 0;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = 0;
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = 0;
PFNGLCREATESHADERPROC glCreateShader = 0;
PFNGLUNIFORM4IPROC glUniform4i = 0;
PFNGLUNIFORM2UIPROC glUniform2ui = 0;
PFNGLDELETESHADERPROC glDeleteShader = 0;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = 0;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = 0;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = 0;
PFNGLLINKPROGRAMPROC glLinkProgram = 0;
PFNGLBINDBUFFERPROC glBindBuffer = 0;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = 0;
PFNGLUNIFORM3IPROC glUniform3i = 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = 0;
PFNGLUNIFORM1FPROC glUniform1f = 0;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = 0;
PFNGLUSEPROGRAMPROC glUseProgram = 0;
PFNGLUNIFORM4UIPROC glUniform4ui = 0;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = 0;
PFNGLACTIVETEXTUREPROC glActiveTexture = 0;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = 0;
PFNGLBUFFERDATAPROC glBufferData = 0;
PFNGLATTACHSHADERPROC glAttachShader = 0;
PFNGLUNIFORM1IPROC glUniform1i = 0;
PFNGLCREATEPROGRAMPROC glCreateProgram = 0;
PFNGLUNIFORM4FPROC glUniform4f = 0;
PFNGLCOMPILESHADERPROC glCompileShader = 0;

void loadOpenGLFunctions()
{
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)(wglGetProcAddress("glDeleteProgram"));
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)(wglGetProcAddress("glUniformMatrix4fv"));
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)(wglGetProcAddress("glGetShaderInfoLog"));
	glGenBuffers = (PFNGLGENBUFFERSPROC)(wglGetProcAddress("glGenBuffers"));
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)(wglGetProcAddress("glDeleteBuffers"));
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)(wglGetProcAddress("glGetProgramiv"));
	glUniform3ui = (PFNGLUNIFORM3UIPROC)(wglGetProcAddress("glUniform3ui"));
	glUniform3f = (PFNGLUNIFORM3FPROC)(wglGetProcAddress("glUniform3f"));
	glGetShaderiv = (PFNGLGETSHADERIVPROC)(wglGetProcAddress("glGetShaderiv"));
	glUniform2i = (PFNGLUNIFORM2IPROC)(wglGetProcAddress("glUniform2i"));
	glShaderSource = (PFNGLSHADERSOURCEPROC)(wglGetProcAddress("glShaderSource"));
	glUniform1ui = (PFNGLUNIFORM1UIPROC)(wglGetProcAddress("glUniform1ui"));
	glUniform2f = (PFNGLUNIFORM2FPROC)(wglGetProcAddress("glUniform2f"));
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)(wglGetProcAddress("glBindVertexArray"));
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)(wglGetProcAddress("wglChoosePixelFormatARB"));
	glCreateShader = (PFNGLCREATESHADERPROC)(wglGetProcAddress("glCreateShader"));
	glUniform4i = (PFNGLUNIFORM4IPROC)(wglGetProcAddress("glUniform4i"));
	glUniform2ui = (PFNGLUNIFORM2UIPROC)(wglGetProcAddress("glUniform2ui"));
	glDeleteShader = (PFNGLDELETESHADERPROC)(wglGetProcAddress("glDeleteShader"));
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)(wglGetProcAddress("glDeleteVertexArrays"));
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)(wglGetProcAddress("glGetProgramInfoLog"));
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)(wglGetProcAddress("wglCreateContextAttribsARB"));
	glLinkProgram = (PFNGLLINKPROGRAMPROC)(wglGetProcAddress("glLinkProgram"));
	glBindBuffer = (PFNGLBINDBUFFERPROC)(wglGetProcAddress("glBindBuffer"));
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)(wglGetProcAddress("glGetUniformLocation"));
	glUniform3i = (PFNGLUNIFORM3IPROC)(wglGetProcAddress("glUniform3i"));
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)(wglGetProcAddress("glEnableVertexAttribArray"));
	glUniform1f = (PFNGLUNIFORM1FPROC)(wglGetProcAddress("glUniform1f"));
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)(wglGetProcAddress("glGenVertexArrays"));
	glUseProgram = (PFNGLUSEPROGRAMPROC)(wglGetProcAddress("glUseProgram"));
	glUniform4ui = (PFNGLUNIFORM4UIPROC)(wglGetProcAddress("glUniform4ui"));
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)(wglGetProcAddress("glValidateProgram"));
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)(wglGetProcAddress("glActiveTexture"));
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)(wglGetProcAddress("glVertexAttribPointer"));
	glBufferData = (PFNGLBUFFERDATAPROC)(wglGetProcAddress("glBufferData"));
	glAttachShader = (PFNGLATTACHSHADERPROC)(wglGetProcAddress("glAttachShader"));
	glUniform1i = (PFNGLUNIFORM1IPROC)(wglGetProcAddress("glUniform1i"));
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)(wglGetProcAddress("glCreateProgram"));
	glUniform4f = (PFNGLUNIFORM4FPROC)(wglGetProcAddress("glUniform4f"));
	glCompileShader = (PFNGLCOMPILESHADERPROC)(wglGetProcAddress("glCompileShader"));
}
#endif
