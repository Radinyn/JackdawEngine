#pragma once
#include "../core/glfunctions.h"
#include <vector>
#include <type_traits>
#include <string>

class VertexBuffer
{
private:
	GLuint mID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};


class IndexBuffer
{
private:
	GLuint mID;
	unsigned int mCount;
public:
	IndexBuffer(const GLuint* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	GLuint getCount() const;
};


struct VertexBufferElement
{
	GLuint type;
	unsigned int count;

	static unsigned int getSizeOfType(GLuint type)
	{
		switch (type)
		{
		case GL_FLOAT:			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:	return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:	return sizeof(GLbyte);
		}
		return 0;
	}
};


class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> mElements;
	unsigned int mStride;

public:
	VertexBufferLayout() :
		mStride(0) {}


	template <class T>
	void push(unsigned int count)
	{
		if constexpr (std::is_same_v<T, GLfloat>)
		{
			mElements.push_back({ GL_FLOAT, count });
			mStride += count * sizeof(GLfloat);
		}
		else if constexpr (std::is_same_v<T, GLuint>)
		{
			mElements.push_back({ GL_UNSIGNED_INT, count });
			mStride += count * sizeof(GLuint);
		}
		else if constexpr (std::is_same_v<T, GLubyte>)
		{
			mElements.push_back({ GL_UNSIGNED_BYTE, count });
			mStride += count * sizeof(GLubyte);
		}
	}

	const std::vector<VertexBufferElement>& getElements() const { return this->mElements; }
	unsigned int getStride() const { return this->mStride; }

};


class VertexArray
{
private:
	GLuint mID;

public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void bind() const;
	void unbind() const;
};

// Class for storing data needed to draw objects
class GLObject
{
public:
	VertexArray* pVA;
	VertexBuffer* pVB;
	IndexBuffer* pIB;

	GLObject() : pVA(nullptr), pVB(nullptr), pIB(nullptr) {}

	~GLObject()
	{
		delete pVA;
		delete pVB;
		delete pIB;
	}

	void bind() const
	{
		pVA->bind();
		pIB->bind();
	}

	unsigned int getVertexCount() const
	{
		return pIB->getCount();
	}

};

void loadObj(GLObject* glObj, const std::string& filepath, bool hasTexture, bool hasNormals);