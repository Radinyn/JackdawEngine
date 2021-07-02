#include "glclasses.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &mID);
	glBindBuffer(GL_ARRAY_BUFFER, mID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &mID);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mID);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



IndexBuffer::IndexBuffer(const GLuint* data, unsigned int count)
{
	glGenBuffers(1, &mID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	this->mCount = count;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &mID);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const { return this->mCount; }


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &mID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mID);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	this->bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.getStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}

}

void VertexArray::bind() const
{
	glBindVertexArray(mID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

