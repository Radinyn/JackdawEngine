#pragma once
#include <string>
#include <chrono>
#include <thread>
#include "JackdawGraphics.h"
#include "JackdawAudio.h"

namespace jdw
{
	enum class KEY {
		LMB = 0x01, RMB, MMB = 0x04,
		ZERO = 0x30, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		SHIFT = 0x10, LSHIFT = 0xA0, RSHIFT,
		CTRL = 0x11, LCTRL = 0xA2, RCTRL,
		ENTER = 0x0D, SPACE = 0x20,
		TAB = 0x09, RALT = 0x12,
		ESCAPE = 0x1B, BACKSPACE = 0x08,
		NUM0 = 0x60, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
		F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F11, F12,
		LEFT = 0x25, UP, RIGHT, DOWN,
	};
	

	// Singleton class, menages everything in the global scope
	class Application
	{
	private:
		inline static void* mWindow;
		inline static std::vector<void*> mShaders;
		inline static Camera* mCamera;
		inline static Vec4f mFillColor;
		inline static int mWidth, mHeight;
		inline static Mat4f mOrthoMatrix;
		inline static bool mCursorState;
		inline static float mDeltaTime;
		inline static std::chrono::steady_clock::time_point mTimeOld, mTimeNew;
		inline static std::thread* mAudioThread;
	public:
		static void init(unsigned int width, unsigned int height, const wchar_t* windowName, bool fullscreen);
		static void terminate();
		static bool run();
		static void close();

		friend class Camera;

		/* Defined in core */
		friend void showCursor();
		friend void hideCursor();
		friend bool getCursorState();
		friend bool isFocused();
		friend unsigned int getWidth();
		friend unsigned int getHeight();
		friend bool isHeld(KEY key);
		friend bool wasPressed(KEY key);
		friend bool wasReleased(KEY key);
		friend double getWheelDelta();
		friend Vec2f getMousePosition();
		friend void setMousePosition(Vec2f position);
		friend Vec2f convertToNDC(Vec2f coords);
		friend double getDeltaTime();

		/* Defined in graphics */
		friend void enableMeshMode();
		friend void disableMeshMode();
		friend void setFillColor(Vec4f color);
		friend Vec4f getFillColor();
		friend void bindCamera(Camera* camera);
		friend void draw(Sprite& sprite);
		friend void draw(Drawable& drawable);
		friend void draw(Text& text);
		friend void render(Model& model);

	};

	void showCursor();
	void hideCursor();
	bool getCursorState();
	bool isFocused();
	unsigned int getWidth();
	unsigned int getHeight();
	bool isHeld(KEY key);
	bool wasPressed(KEY key);
	bool wasReleased(KEY key);
	double getWheelDelta();
	Vec2f getMousePosition();
	void setMousePosition(Vec2f position);
	Vec2f convertToNDC(Vec2f coords);
	double getDeltaTime();
	void enableMeshMode();
	void disableMeshMode();
	void setFillColor(Vec4f color);
	Vec4f getFillColor();
	void bindCamera(Camera* camera);
	void draw(Sprite& sprite);
	void draw(Drawable& drawable);
	void draw(Text& text);
	void render(Model& model);

}