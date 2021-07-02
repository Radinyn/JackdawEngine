#include "../../include/JackdawGraphics.h"
#include "../graphics/glclasses.h"
#include "shaderList.h"
#include "shader.h"

namespace jdw
{
    Model::Model(const std::string& filepath,
			     Texture* texture,
			     LIGHTING lighting,
		         const Material& material,
			     const Vec4f& color,
			     bool hasNormals)
    {
        this->lighting = lighting;
        this->mHasTexture = texture ? 1 : 0;
        this->mHasNormals = hasNormals;
        this->mTexture = texture;
        this->material = material;
        this->mGLData = new GLObject;
        loadObj((GLObject*)this->mGLData, filepath, this->mHasTexture, hasNormals);
		this->color = color;
		this->mScale =    { 1, 1, 1 };
		this->mPosition = { 0, 0, 0 };
		this->mRotation = { 0, 0, 0 };
		this->mNeedsRecalculation = 1;
    }

    Model::~Model() { delete (GLObject*)this->mGLData; }
}