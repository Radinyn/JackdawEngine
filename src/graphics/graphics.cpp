#include "../../include/JackdawCore.h"
#include "../graphics/glclasses.h"
#include "shaderList.h"
#include "shader.h"

namespace jdw
{

	void enableMeshMode()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void disableMeshMode()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void setFillColor(Vec4f color)
	{
		Application::mFillColor = color;
		glClearColor(color.r, color.g, color.b, color.a);
	}

	Vec4f getFillColor()
	{
		return Application::mFillColor;
	}

	void bindCamera(Camera* camera)
	{
		Application::mCamera = camera;
	}

	// Typedef for macro
	typedef unsigned int uint;

	#define IF___CHECK_AND_SET_UNIVAL(TYPE) if (const TYPE* p = std::get_if<TYPE>(&value)) shader->setUniform(name, *p)
	#define ELIF_CHECK_AND_SET_UNIVAL(TYPE) else if (const TYPE* p = std::get_if<TYPE>(&value)) shader->setUniform(name, *p)

	void _setUniforms(Shader* shader, UniformMap& uniMap)
	{
			for (const auto& [name, value] : uniMap)
			{
				IF___CHECK_AND_SET_UNIVAL(int);
				ELIF_CHECK_AND_SET_UNIVAL(Vec2i);
				ELIF_CHECK_AND_SET_UNIVAL(Vec3i);
				ELIF_CHECK_AND_SET_UNIVAL(Vec4i);
				ELIF_CHECK_AND_SET_UNIVAL(uint);
				ELIF_CHECK_AND_SET_UNIVAL(Vec2ui);
				ELIF_CHECK_AND_SET_UNIVAL(Vec3ui);
				ELIF_CHECK_AND_SET_UNIVAL(Vec4ui);
				ELIF_CHECK_AND_SET_UNIVAL(float);
				ELIF_CHECK_AND_SET_UNIVAL(Vec2f);
				ELIF_CHECK_AND_SET_UNIVAL(Vec3f);
				ELIF_CHECK_AND_SET_UNIVAL(Vec4f);
				ELIF_CHECK_AND_SET_UNIVAL(Mat4f);
			}
	}

	void draw(Polygon& polygon, CustomShader* customShader)
	{
		if (polygon.mNeedsRecalculation)
		{
			polygon.mNeedsRecalculation = 0;
			polygon.recalculateMatrix();
		}

		GLObject* glData = (GLObject*) polygon.mGLData;
		glData->bind();

		Shader* shader;
		if (customShader)
		{
			shader = (Shader*) customShader->innerShader;
			shader->bind();
			if (customShader->uniMap)
				_setUniforms(shader, *(customShader->uniMap));
		}
		else
		{
			shader = (Shader*) Application::mShaders[(int)SHADER::t0n0lN];
			shader->bind();
		}


		shader->setUniform("uProj", Application::mOrthoMatrix); // TODO_FAR: can be optimized further
		shader->setUniform("uMV", polygon.mMatrix); // ...
		shader->setUniform("uColor", polygon.color); // by moving it into setup / getters and setters
		
		glDisable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, glData->getVertexCount(), GL_UNSIGNED_INT, nullptr);
		glEnable(GL_DEPTH_TEST);
	}

	void draw(Sprite& sprite, CustomShader* customShader)
	{
		if (sprite.mNeedsRecalculation)
		{
			sprite.mNeedsRecalculation = 0;
			sprite.recalculateMatrix();
		}

		GLObject* glData = (GLObject*) sprite.mGLData;
		glData->bind();

		Shader* shader;
		if (customShader)
		{
			shader = (Shader*) customShader->innerShader;
			shader->bind();
			if (customShader->uniMap)
				_setUniforms(shader, *(customShader->uniMap));
		}
		else
		{
			shader = (Shader*) Application::mShaders[(int)SHADER::t1n0lN];
			shader->bind();
		}

		const int slot = 0;
		sprite.mTexture->bind(slot); // TODO: Implement texture slotting system

		shader->setUniform("uProj", Application::mOrthoMatrix); // TODO_FAR: can be optimized further
		shader->setUniform("uMV", sprite.mMatrix); // ...
		shader->setUniform("uTexture", slot); // by moving it into setup / getters and setters

		glDisable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, glData->getVertexCount(), GL_UNSIGNED_INT, nullptr);
		glEnable(GL_DEPTH_TEST);
	}

	void draw(Text& text, CustomShader* customShader)
	{
		if (text.mNeedsRecalculation)
		{
			text.mNeedsRecalculation = 0;
			text.recalculateMatrix();
		}

		GLObject* glData = (GLObject*) text.mGLData;
		glData->bind();

		Shader* shader;
		if (customShader)
		{
			shader = (Shader*) customShader->innerShader;
			shader->bind();
			if (customShader->uniMap)
				_setUniforms(shader, *(customShader->uniMap));
		}
		else
		{
			shader = (Shader*) Application::mShaders[(int)SHADER::textShader];
			shader->bind();
		}

		const int slot = 0;
		text.mFont->bind(slot); // TODO: Implement texture slotting system

		shader->setUniform("uProj", Application::mOrthoMatrix); // TODO_FAR: can be optimized further
		shader->setUniform("uMV", text.mMatrix); // ...
		shader->setUniform("uTexture", slot); // by moving it into setup / getters and setters
		shader->setUniform("uColor", text.color);

		glDisable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, glData->getVertexCount(), GL_UNSIGNED_INT, nullptr);
		glEnable(GL_DEPTH_TEST);
	}

	void drawLine(const Vec2f& a, const Vec2f& b, const Vec4f& color, float width)
	{
		// This is actually MUCH faster than sending data to the GPU each frame
		// Create a single square 1x1 and modify it to look like a line

		static Polygon lineBase = {
			{ {0, 0}, {1, 0}, {1, 1}, {0, 1} },
			{0, 0, 0, 1}
		};

		float length = dist(a, b);
		lineBase.setScale({length, width});
		lineBase.setPosition(a);
		lineBase.setRotation((b-a).getAngle());
		lineBase.color = color;
		draw(lineBase);
	}

	static int _getShaderIndex(bool hasTexture, bool hasNormals, LIGHTING lighting)
	{
		unsigned int texPart = hasTexture ? 0x100 : 0x000;
		unsigned int norPart = hasNormals ? 0x010 : 0x000;
		unsigned int ligPart = lighting == LIGHTING::NONE     ? 0x000 :
							   lighting == LIGHTING::REGULAR  ? 0x001 :
							   /*lighting == LIGHTING::FLAT*/   0x002 ;

		unsigned int shaderID = texPart + norPart + ligPart;

		switch (shaderID)
		{
			case 0x000: return (int)SHADER::t0n0lN;
			case 0x010: return (int)SHADER::t0n1lN;
			case 0x100: return (int)SHADER::t1n0lN;
			case 0x110: return (int)SHADER::t1n1lN;
			default:
				throw std::runtime_error("[JDW] [Error] Unable to find the correct shader");
				return 0x000;
		}

	}

	void render(Model& model, CustomShader* customShader)
	{
		if (!Application::mCamera)
			throw std::runtime_error("[JDW] [Error] No camera bound");
		
		if (model.mNeedsRecalculation)
		{
			model.mNeedsRecalculation = 0;
			model.recalculateMatrix();
		}

		if (Application::mCamera->mNeedsRecalculation)
		{
			Application::mCamera->mNeedsRecalculation = 0;
			Application::mCamera->recalculateMatrix();
		}

		if (Application::mCamera->mProjNeedsRecalculation)
		{
			Application::mCamera->mProjNeedsRecalculation = 0;
			Application::mCamera->recalculateProjMatrix();
		}

		GLObject* glData = (GLObject*) model.mGLData;
		glData->bind();

		Shader* shader;
		if (customShader)
		{
			shader = (Shader*) customShader->innerShader;
			shader->bind();
			if (customShader->uniMap)
				_setUniforms(shader, *(customShader->uniMap));
		}
		else
		{
			int shaderIndex = _getShaderIndex(model.mHasTexture, model.mHasNormals, model.lighting);
			shader = (Shader*) Application::mShaders[shaderIndex];
			shader->bind();
		}

		const int slot = 0;
		if (model.mHasTexture)
			model.mTexture->bind(slot); // TODO: Implement texture slotting system

		shader->setUniform("uProj", Application::mCamera->mProjMatrix);
		const Mat4f mv = model.mMatrix * Application::mCamera->mMatrix;
		shader->setUniform("uMV", mv);

		if (model.mHasTexture)
			shader->setUniform("uTexture", slot);
		else
			shader->setUniform("uColor", model.color);

		glDrawElements(GL_TRIANGLES, glData->getVertexCount(), GL_UNSIGNED_INT, nullptr);
	}
}