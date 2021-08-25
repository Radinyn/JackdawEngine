#include "../../include/JackdawGraphics.h"
#include "../graphics/glclasses.h"
#include "../vendor/stb_truetype.h"
#include <iostream>

namespace jdw
{
	Text::Text(Font* font, const std::string& str, const Vec4f& color)
	{
		this->mGLData = new GLObject;
        this->color = color;
        const size_t& n = str.length();

        this->mFont = font;

        std::vector<_Vector4Type<GLfloat>> vertexBufferVector(n * 4);
        std::vector<GLuint> indexBufferVector(n * 6);

        VertexBufferLayout layout;
		layout.push<GLfloat>(2);
        layout.push<GLfloat>(2);

        float x = 0, y = 0;

        for (int i = 0; i < n; i++)
        {
            const char& c = str[i];

            if (!(c >= 32 && c < 128))
                throw std::runtime_error("[JDW] [Error] Illegal character in Text");

            stbtt_aligned_quad q;
            stbtt_GetBakedQuad((const stbtt_bakedchar *)mFont->mBakedChars, 512, 512, c-32, &x, &y, &q, 1);

            // TODO: Use unordered_map to decrease the size of the indexBufferVector

            vertexBufferVector[i*4+0] = {q.x0, -q.y1, q.s0, q.t1};
            vertexBufferVector[i*4+1] = {q.x1, -q.y1, q.s1, q.t1};
            vertexBufferVector[i*4+2] = {q.x1, -q.y0, q.s1, q.t0};
            vertexBufferVector[i*4+3] = {q.x0, -q.y0, q.s0, q.t0};

            indexBufferVector[i*6+0] = i*4+0;
            indexBufferVector[i*6+1] = i*4+1;
            indexBufferVector[i*6+2] = i*4+2;
            indexBufferVector[i*6+3] = i*4+2;
            indexBufferVector[i*6+4] = i*4+3;
            indexBufferVector[i*6+5] = i*4+0;
        }

        VertexArray* va = new VertexArray;
        VertexBuffer* vb = new VertexBuffer(&vertexBufferVector[0], vertexBufferVector.size() * 4 * sizeof(GLfloat));
        IndexBuffer* ib = new IndexBuffer(&indexBufferVector[0], indexBufferVector.size());

        va->bind();
        va->addBuffer(*vb, layout);

        ((GLObject*)mGLData)->pVA = va;
        ((GLObject*)mGLData)->pVB = vb;
        ((GLObject*)mGLData)->pIB = ib;

		this->mScale = { 1, 1 };
		this->mPosition = { 0, 0 };
		this->mRotation = 0;
		this->mNeedsRecalculation = 1;
	}

	Text::~Text() { delete (GLObject*)mGLData; }
}