#include "../../include/JackdawGraphics.h"
#include "../graphics/glclasses.h"
#include "shaderList.h"
#include "shader.h"

namespace jdw
{
	static void _innerSpriteConstructor(GLObject* glObj, const Vec2f* boundingPoints)
	{
		GLfloat vertexBufferArray[] =
        {
            boundingPoints[0].x, boundingPoints[0].y, 0, 0,
            boundingPoints[1].x, boundingPoints[1].y, 1, 0,
            boundingPoints[2].x, boundingPoints[2].y, 1, 1,
            boundingPoints[3].x, boundingPoints[3].y, 0, 1,
        };

        GLuint indexBufferArray[] =
        {
            0, 1, 2,
            2, 3, 0
        };

		VertexBufferLayout layout;
		layout.push<GLfloat>(2);
        layout.push<GLfloat>(2);

		VertexArray* va = new VertexArray;
		VertexBuffer* vb = new VertexBuffer(vertexBufferArray, 16 * sizeof(GLfloat));
		IndexBuffer* ib = new IndexBuffer(indexBufferArray, 6);

		va->bind();
		va->addBuffer(*vb, layout);

		delete glObj->pVA;
		delete glObj->pVB;
		delete glObj->pIB;

		glObj->pVA = va;
		glObj->pVB = vb;
		glObj->pIB = ib;
	}
    
    Sprite::Sprite(Texture* texture)
    {
        this->mTexture = texture;
        this->mGLData = new GLObject; 
        const float height = (float)texture->getHeight();
        const float width = (float)texture->getWidth();
        mBoundingPoints[0] = {0, 0};
        mBoundingPoints[1] = {width, 0};
        mBoundingPoints[2] = {width, height};
        mBoundingPoints[3] = {0, height};

        _innerSpriteConstructor((GLObject*)this->mGLData, mBoundingPoints);

		this->mScale = { 1, 1 };
		this->mPosition = { 0, 0 };
		this->mRotation = 0;
		this->mNeedsRecalculation = 1;
    }

    Sprite::Sprite(Texture* texture, float width, float height)
    {
        this->mTexture = texture;
        this->mGLData = new GLObject; 
        mBoundingPoints[0] = {0, 0};
        mBoundingPoints[1] = {width, 0};
        mBoundingPoints[2] = {width, height};
        mBoundingPoints[3] = {0, height};

        _innerSpriteConstructor((GLObject*)this->mGLData, mBoundingPoints);

		this->mScale = { 1, 1 };
		this->mPosition = { 0, 0 };
		this->mRotation = 0;
		this->mNeedsRecalculation = 1;
    }

    Sprite::Sprite(Texture* texture, const Vec2f& bottomLeft, const Vec2f& bottomRight, const Vec2f& topRight, const Vec2f& topLeft)
    {
        this->mTexture = texture;
        this->mGLData = new GLObject; 
        mBoundingPoints[0] = bottomLeft;
        mBoundingPoints[1] = bottomRight;
        mBoundingPoints[2] = topRight;
        mBoundingPoints[3] = topLeft;

        _innerSpriteConstructor((GLObject*)this->mGLData, mBoundingPoints);

		this->mScale = { 1, 1 };
		this->mPosition = { 0, 0 };
		this->mRotation = 0;
		this->mNeedsRecalculation = 1;
    }




    Sprite::~Sprite() { delete (GLObject*)this->mGLData; }
}