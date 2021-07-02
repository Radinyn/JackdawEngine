#include "../../include/JackdawCore.h"

namespace jdw
{
    void Camera::recalculateProjMatrix()
    {
        mProjMatrix = constructPerspf(Application::mWidth/Application::mHeight, mFOV, mNear, mFar);
    }

    Camera::Camera(float fov, float zNear, float zFar, bool bind)
    {
        this->mNeedsRecalculation = 1;
        this->mProjNeedsRecalculation = 1;
        this->mScale    = { 1, 1, 1 };
		this->mPosition = { 0, 0, 0 };
		this->mRotation = { 0, 0, 0 };
        this->mFOV = fov;
        this->mNear = zNear;
        this->mFar = zFar;

        if (bind) bindCamera(this);
    }
}