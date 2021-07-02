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

	void draw(Drawable& drawable)
	{
		if (drawable.mNeedsRecalculation)
		{
			drawable.mNeedsRecalculation = 0;
			drawable.recalculateMatrix();
		}

		GLObject* glData = (GLObject*) drawable.mGLData;
		glData->bind();

		Shader* shader = (Shader*) Application::mShaders[(int)SHADER::t0n0lN];
		shader->bind();

		const Vec4f& col = drawable.color;
		shader->setUniform("uProj", Application::mOrthoMatrix); // TODO_FAR: can be optimized further
		shader->setUniform("uMV", drawable.mMatrix); // ...
		shader->setUniform("uColor", col.r, col.g, col.b, col.a); // by moving it into setup / getters and setters

		glDisable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, glData->getVertexCount(), GL_UNSIGNED_INT, nullptr);
		glEnable(GL_DEPTH_TEST);
	}

	void draw(Sprite& sprite)
	{
		if (sprite.mNeedsRecalculation)
		{
			sprite.mNeedsRecalculation = 0;
			sprite.recalculateMatrix();
		}

		GLObject* glData = (GLObject*) sprite.mGLData;
		glData->bind();

		Shader* shader = (Shader*) Application::mShaders[(int)SHADER::t1n0lN];
		shader->bind();

		const int slot = 0;
		sprite.mTexture->bind(slot); // TODO: Implement texture slotting system

		shader->setUniform("uProj", Application::mOrthoMatrix); // TODO_FAR: can be optimized further
		shader->setUniform("uMV", sprite.mMatrix); // ...
		shader->setUniform("uTexture", slot); // by moving it into setup / getters and setters

		glDisable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, glData->getVertexCount(), GL_UNSIGNED_INT, nullptr);
		glEnable(GL_DEPTH_TEST);
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

	void render(Model& model)
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

		int shadeIndex = _getShaderIndex(model.mHasTexture, model.mHasNormals, model.lighting);
		Shader* shader = (Shader*) Application::mShaders[shadeIndex];
		shader->bind();

		const int slot = 0;
		if (model.mHasTexture)
			model.mTexture->bind(slot); // TODO: Implement texture slotting system

		shader->setUniform("uProj", Application::mCamera->mProjMatrix);
		const Mat4f mv = model.mMatrix * Application::mCamera->mMatrix;
		shader->setUniform("uMV", mv);

		if (model.mHasTexture)
			shader->setUniform("uTexture", slot);
		else
		{
			const Vec4f& col = model.color;
			shader->setUniform("uColor", col.r, col.g, col.b, col.a);
		}

		glDrawElements(GL_TRIANGLES, glData->getVertexCount(), GL_UNSIGNED_INT, nullptr);
	}
}