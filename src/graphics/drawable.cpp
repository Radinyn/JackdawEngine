#include "../../include/JackdawGraphics.h"
#include "../graphics/glclasses.h"
#include "shaderList.h"
#include "shader.h"

namespace jdw
{
	static void _innerDrawableConstructor(GLObject* glObj, const Vec2f* points, int length)
	{
		std::vector<GLfloat> vertexBufferVector(length*2);
		std::vector<GLuint> indexBufferVector((length-2)*3);

		VertexBufferLayout layout;
		layout.push<GLfloat>(2);

		if (length < 3)
			throw std::runtime_error("[JDW] [Error] Too few points in the drawable constructor");

		for (unsigned int i = 0; i < length; i++)
		{
			vertexBufferVector[2*i  ] = points[i].x;
			vertexBufferVector[2*i+1] = points[i].y;
			
			if (i < length - 2)
			{
				indexBufferVector[i*3  ] = 0;
				indexBufferVector[i*3+1] = i + 1;
				indexBufferVector[i*3+2] = i + 2;
			}
		}

		VertexArray* va = new VertexArray;
		VertexBuffer* vb = new VertexBuffer(&vertexBufferVector[0], vertexBufferVector.size() * sizeof(GLfloat));
		IndexBuffer* ib = new IndexBuffer(&indexBufferVector[0], indexBufferVector.size());

		va->bind();
		va->addBuffer(*vb, layout);

		delete glObj->pVA;
		delete glObj->pVB;
		delete glObj->pIB;

		glObj->pVA = va;
		glObj->pVB = vb;
		glObj->pIB = ib;
	}

	Drawable::Drawable(const std::vector<Vec2f>& points, const Vec4f& color)
	{
		this->mGLData = new GLObject;
		_innerDrawableConstructor((GLObject*)this->mGLData, &points[0], points.size());
		this->color = color;
		this->mScale = { 1, 1 };
		this->mPosition = { 0, 0 };
		this->mRotation = 0;
		this->mNeedsRecalculation = 1;
	}

	Drawable::Drawable(Vec2f* points, int length, const Vec4f& color)
	{
		this->mGLData = new GLObject;
		_innerDrawableConstructor((GLObject*)this->mGLData, points, length);
		this->color = color;
		this->mScale = { 1, 1 };
		this->mPosition = { 0, 0 };
		this->mRotation = 0;
		this->mNeedsRecalculation = 1;
	}

	Drawable::~Drawable() { delete (GLObject*)mGLData; }
}