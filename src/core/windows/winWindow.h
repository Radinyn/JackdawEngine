#pragma once
#ifdef _WIN32
#include "winGL.h"
#include <utility>
class winWindow
{
public:
	LPTSTR windowClass;
	HGLRC renderingContext = 0;
	HDC	deviceContext = 0;
	HWND window = 0;
	HINSTANCE instance;
	DWORD style;
	int width, height, posX, posY;

	const wchar_t* title;
	inline static bool keyHeld[256];
	inline static bool keyPressed[256];
	inline static bool keyReleased[256];
	bool active = true;
	bool fullscreen = false;
	inline static bool focused = false;
	inline static double wheelDelta;

	static LRESULT CALLBACK wndProc(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);
	winWindow(int width, int height, const wchar_t* title = L"Hello world!", bool fullscreen = false);
	void create();
	void terminate();
	bool process();
	void showCursor() { ShowCursor(TRUE); }
	void hideCursor() { ShowCursor(FALSE); }
	bool isHeld(int key) const { return keyHeld[key]; }
	bool wasPressed(int key) const { return keyPressed[key]; }
	bool wasReleased(int key) const { return keyReleased[key]; }
	double getWheelDelta() const { return wheelDelta; }
	std::pair<float, float> getMousePosition();
	void setMousePosition(int x, int y);
	bool isFocused() {return focused; }
};
#endif