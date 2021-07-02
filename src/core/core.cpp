
#include "../../include/JackdawCore.h"
#include "window.h"
#include "../graphics/shaderList.h"
#include "../graphics/shader.h"

namespace jdw
{

	void Application::init(unsigned int width, unsigned int height, const wchar_t* windowName, bool fullscreen)
	{
		mHeight = height;
		mWidth = width;
		mFillColor = { 0.1f, 0.1f, 0.1f, 1.0f };
		mCursorState = true;
		mCamera = nullptr;
		mOrthoMatrix = constructOrthof(0, mWidth, 0, mHeight, -1.0f, 1.0f);
		mTimeOld = std::chrono::steady_clock::now();
		mTimeNew = std::chrono::steady_clock::now();

		mWindow = new Window(width, height, windowName, fullscreen);
		((Window*)mWindow)->create();

		// OpenGL setup
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);

		// Load in shaders
		mShaders.resize(_shaders.size());
		for (unsigned int i = 0; i < mShaders.size(); i++)
		{
			mShaders[i] = new Shader(_shaders[i]);
		}

		// start AudioThread
		mAudioThread = new std::thread(AudioManager::process);
	}

	void Application::terminate()
	{
		((Window*)mWindow)->terminate();
		AudioManager::active = false;
		mAudioThread->join();
		delete mAudioThread;
		delete (Window*)mWindow;
	}

	bool Application::run()
	{
		bool status = ((Window*)mWindow)->process();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// calculate time
		mTimeNew = std::chrono::steady_clock::now();
		std::chrono::duration<double> duration = mTimeNew - mTimeOld;
		mDeltaTime = duration.count();
		mTimeOld = mTimeNew;

		return status;
	}

	void Application::close()
	{
		((Window*)mWindow)->active = false;
	}

	void showCursor()
	{
		Application::mCursorState = 1;
		((Window*)Application::mWindow)->showCursor();
	}

	void hideCursor()
	{
		Application::mCursorState = 0;
		((Window*)Application::mWindow)->hideCursor();
	}

	bool getCursorState() { return Application::mCursorState; }
	unsigned int getWidth() { return Application::mWidth; }
	unsigned int getHeight() { return Application::mHeight; }
	bool isHeld(KEY key) { return ((Window*)Application::mWindow)->isHeld((int)key); }
	bool wasPressed(KEY key) { return ((Window*)Application::mWindow)->wasPressed((int)key); }
	bool wasReleased(KEY key) { return ((Window*)Application::mWindow)->wasReleased((int)key); }
	double getWheelDelta() { return ((Window*)Application::mWindow)->getWheelDelta(); }

	Vec2f getMousePosition()
	{
		std::pair<float, float> pos = ((Window*)Application::mWindow)->getMousePosition();
		return { pos.first, pos.second };
	}

	void setMousePosition(Vec2f position)
	{
		((Window*)Application::mWindow)->setMousePosition(position.x, position.y);
	}

	Vec2f convertToNDC(Vec2f coords)
	{
		coords.x /= (Application::mWidth / 2.0f);
		coords.y /= (Application::mHeight / 2.0f);
		coords.x -= 1.0f;
		coords.y -= 1.0f;
		return coords;
	}

	bool isFocused()
	{
		return ((Window*)Application::mWindow)->isFocused();
	}

	double getDeltaTime()
	{
		return Application::mDeltaTime;
	}

}