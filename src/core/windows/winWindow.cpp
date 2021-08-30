#ifdef _WIN32
#include "winWindow.h"
#include <iostream>

#ifdef DEBUGGING_WINDOWS_WINDOW
#define PRINT_DEBUG(x) std::cout << #x << " " << x << std::endl;
#define PRINT_VAR(x) std::cout << #x << " " << x << std::endl;
#else
#define PRINT_DEBUG(x) x
#define PRINT_VAR(x) ;
#endif

#define SET_KEY(x) if (!keyHeld[x]) keyPressed[x] = 1; keyHeld[x] = 1; break;
#define UNSET_KEY(x) if (keyHeld[x]) keyReleased[x] = 1; keyHeld[x] = 0; break;

winWindow::winWindow(int width, int height, const wchar_t* title, bool fullscreen, bool display) :
	width(width), height(height), posX(CW_USEDEFAULT), posY(0), fullscreen(fullscreen), display(display),
	style(WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN), title(title)
{
	wheelDelta = 0.0;
	memset(&keyHeld, 0, 256 * sizeof(bool));
	memset(&keyReleased, 0, 256 * sizeof(bool));
	memset(&keyPressed, 0, 256 * sizeof(bool));
}

LRESULT winWindow::wndProc(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN: SET_KEY(VK_LBUTTON)
	case WM_RBUTTONDOWN: SET_KEY(VK_RBUTTON)
	case WM_MBUTTONDOWN: SET_KEY(VK_MBUTTON)
	case WM_KEYDOWN: SET_KEY(wParam)

	case WM_LBUTTONUP: UNSET_KEY(VK_LBUTTON)
	case WM_RBUTTONUP: UNSET_KEY(VK_RBUTTON)
	case WM_MBUTTONUP: UNSET_KEY(VK_MBUTTON)
	case WM_KEYUP: UNSET_KEY(wParam)

	case WM_MOUSEWHEEL:
		wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_SETFOCUS:
		focused = 1;
		break;
	
	case WM_KILLFOCUS:
		focused = 0;
		break;

	default:
		return DefWindowProc(hWND, message, wParam, lParam);
	}
	return 0;
}

void winWindow::create()
{

	/* Note, may conflict with DLL, for now export only as static lib */
	this->instance = GetModuleHandle(NULL);
	
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(wcex));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = (WNDPROC)wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->instance;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Icon loader, to be added in the future
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // Cursor loader, to be added in a much further future
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"OpenGL";

	this->windowClass = MAKEINTATOM(RegisterClassEx(&wcex));
	PRINT_VAR(this->windowClass);

	/* Create a dummy context in order to load OpenGL functions; */

	HWND dummyWindow = CreateWindow(
		this->windowClass,
		L"Dummy Title",
		this->style,
		0, 0, 1, 1,
		NULL, NULL,
		this->instance, NULL
	);

	HDC dummyDC = GetDC(dummyWindow);

	PIXELFORMATDESCRIPTOR dummyPFD;
	memset(&dummyPFD, 0, sizeof(dummyPFD));
	dummyPFD.nSize = sizeof(dummyPFD);
	dummyPFD.nVersion = 1;
	dummyPFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	dummyPFD.iPixelType = PFD_TYPE_RGBA;
	dummyPFD.cColorBits = 32;
	dummyPFD.cAlphaBits = 8;
	dummyPFD.cDepthBits = 24;

	const int dummyPFDID = ChoosePixelFormat(dummyDC, &dummyPFD);
	PRINT_VAR(dummyPFDID)

	PRINT_DEBUG(SetPixelFormat(dummyDC, dummyPFDID, &dummyPFD));
	HGLRC dummyRC = wglCreateContext(dummyDC);
	PRINT_VAR(dummyDC);
	PRINT_DEBUG(wglMakeCurrent(dummyDC, dummyRC));

	//------------------//
	loadOpenGLFunctions();
	//------------------//

	/* Adjust size according to the window's menu */

	int tempWidth = this->width;
	int tempHeight = this->height;

	if (this->display)
	{
		if (!this->fullscreen)
		{
			RECT wndRect = { 0, 0, this->width, this->height };
			AdjustWindowRect(&wndRect, this->style, FALSE);
			tempWidth = wndRect.right - wndRect.left;
			tempHeight = wndRect.bottom - wndRect.top;
		}
	}

	/* Create the actual window */

	this->window = CreateWindow(
		this->windowClass,
		this->title,
		this->style,
		this->posX, this->posY,
		tempWidth, tempHeight,
		NULL, NULL,
		this->instance, NULL
	);

	this->deviceContext = GetDC(this->window);

	const int pixelAttribs[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, 4,
		0
	};

	int pixelFormatID; UINT numFormats;
	PRINT_DEBUG(wglChoosePixelFormatARB(this->deviceContext, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats));
	PRINT_VAR(numFormats);

	PIXELFORMATDESCRIPTOR PFD;
	PRINT_DEBUG(DescribePixelFormat(this->deviceContext, pixelFormatID, sizeof(PFD), &PFD));
	PRINT_DEBUG(SetPixelFormat(this->deviceContext, pixelFormatID, &PFD));

	const int contextAttribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 0,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	this->renderingContext = wglCreateContextAttribsARB(this->deviceContext, 0, contextAttribs);
	PRINT_VAR(this->renderingContext);

	// Destroy dummy context
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(dummyRC);
	ReleaseDC(dummyWindow, dummyDC);
	DestroyWindow(dummyWindow);

	// Start the new window

	PRINT_DEBUG(wglMakeCurrent(this->deviceContext, this->renderingContext));

	SetWindowText(this->window, this->title);

	/* Temporarly here in case they are needed in the future */
	// STARTUPINFO startupInfo;
	// GetStartupInfo(&startupInfo);

	ShowWindow(this->window, SW_SHOWDEFAULT);

	
	if (!this->display)
	{
		HWND handle = GetActiveWindow();
		SetWindowPos(
		handle,
		HWND_TOP,
		this->posX, this->posY,
		tempWidth, tempHeight,
		SWP_NOSENDCHANGING
		);
	}
	
}

void winWindow::terminate()
{
	wglMakeCurrent(NULL, NULL);
	if (this->renderingContext) wglDeleteContext(this->renderingContext);
	if (this->deviceContext) ReleaseDC(this->window, this->deviceContext);
	if (this->window) DestroyWindow(this->window);
}

bool winWindow::process()
{
	memset(&keyReleased, 0, 256 * sizeof(bool));
	memset(&keyPressed, 0, 256 * sizeof(bool));
	wheelDelta = 0;

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		switch (msg.message)
		{
		case WM_QUIT:
			this->active = false;
			break;

		default: break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (!this->display)
	{
		HWND handle = GetActiveWindow();
		SetWindowPos(
		handle,
		HWND_TOP,
		this->posX, this->posY,
		this->width, this->height,
		SWP_NOSENDCHANGING | SWP_NOMOVE
		);
		glViewport(0, 0, width, height);
	}

	SwapBuffers(this->deviceContext);

	return this->active;
}

std::pair<float, float> winWindow::getMousePosition()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(this->window, &point);
	point.y = this->height - point.y;
	return { point.x, point.y };
}

void winWindow::setMousePosition(int x, int y)
{
	POINT point;
	point.x = x;
	point.y = this->height-y;
	ClientToScreen(this->window, &point);
	if (this->focused)
		SetCursorPos(point.x, point.y);
}

#endif