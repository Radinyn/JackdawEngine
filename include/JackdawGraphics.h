#pragma once
#include "JackdawMath.h"
#include "JackdawCustomShader.h"
#include <vector>
#include <string>

namespace jdw
{
	// Abstract classes for drawing purposes
	class _Entity3D
	{
	protected:
		Mat4f mMatrix;
		Vec3f mPosition, mScale, mRotation;
		bool mNeedsRecalculation;
		virtual void recalculateMatrix() = 0;
	public:
		void setPosition(const Vec3f& position) { mPosition = position; mNeedsRecalculation = 1; }
		Vec3f getPosition() const { return mPosition; }
		void setScale(const Vec3f& scale) { mScale = scale; mNeedsRecalculation = 1; }
		Vec3f getScale() const { return mScale; }
		void setRotation(const Vec3f& rotation) { mRotation = rotation; mNeedsRecalculation = 1; }
		Vec3f getRotation() const { return mRotation; }
		virtual Vec3f getDir() const = 0;
	};

	class _Entity2D
	{
	protected:
		void* mGLData;
		Mat4f mMatrix;
		float mRotation;
		Vec2f mScale, mPosition;
		bool mNeedsRecalculation;

		void recalculateMatrix()
		{
			Mat4f rot = constructRotateZf(this->mRotation);
			Mat4f pos  = constructTranslatef(this->mPosition);
			Mat4f scale = constructScalef(this->mScale);
			this->mMatrix = scale * rot * pos;
		}

	public:
		void setPosition(const Vec2f& position) { mPosition = position; mNeedsRecalculation = 1; }
		Vec2f getPosition() const { return mPosition; }
		void setScale(const Vec2f& scale) { mScale = scale; mNeedsRecalculation = 1; }
		Vec2f getScale() const { return mScale; }
		void setRotation(float rotation) { mRotation = rotation; mNeedsRecalculation = 1; }
		float getRotation() const { return mRotation; }
	};

	class Texture
	{
	private:
		unsigned int mID;
		unsigned char* mBuffer;
		int mWidth, mHeight, mBPP;

	public:
		Texture(const char* filepath, bool pixelart = false);
		~Texture();
		Texture(const Texture&) = delete;

		int getWidth() const { return this->mWidth; }
		int getHeight() const { return this->mHeight; }
		void bind(unsigned int slot = 0);
		void unbind();
	};

	class Font
	{
	private:
		static constexpr int mCapacity = 1<<20;
		static constexpr int mBitmapSize = 512*512;
		unsigned int mID;
		unsigned char* mBuffer;
		unsigned char* mBitmap;
		void* mBakedChars;

	public:
		/* Filepath to a ttf file */
		Font(const char* filepath, unsigned int fontSize = 32, bool pixelart = false);
		~Font();

		void bind(unsigned int slot = 0);
		void unbind();

		friend class Text;
	};

	// o--------o
	// | #1. 2D |
	// o--------o

	class Sprite : public _Entity2D
	{
	private:
		Texture* mTexture;
		Vec2f mBoundingPoints[4];
	public:
		Sprite(Texture* texture);
		Sprite(Texture* texture, float width, float height);
		Sprite(Texture* texture, const Vec2f& bottomLeft, const Vec2f& bottomRight,
								 const Vec2f& topRight,   const Vec2f& topLeft);
		~Sprite();
		Sprite(const Sprite&) = delete;

		friend void draw(Sprite& sprite, CustomShader* customShader);
	};

	class Polygon : public _Entity2D
	{
	public:
		Vec4f color;

		// Draw a CONVEX polygon!
		Polygon(const std::vector<Vec2f>& points, const Vec4f& color);
		// Draw a CONVEX polygon!
		Polygon(Vec2f* points, int length, const Vec4f& color);
		~Polygon();
		Polygon(const Polygon&) = delete;

		friend void draw(Polygon& Polygon, CustomShader* customShader);
	};

	class Text : public _Entity2D
	{
	private:
		Font* mFont;

	public:
		Vec4f color;

		Text(Font* font, const std::string& str, const Vec4f& color);
		~Text();
		Text(const Text&) = delete;

		friend void draw(Text& text, CustomShader* customShader);
	};

	// o--------o
	// | #2. 3D |
	// o--------o

	enum class LIGHTING
	{
		NONE,
		REGULAR,
		FLAT // low-poly
	};

	class Material
	{
	public:
		Vec4f ambientColor, diffuseColor, specularColor;
		float shine;
		Material(Vec4f ambientColor, Vec4f diffuseColor, Vec4f specularColor, float shine) :
			ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor), shine(shine) {}
		Material() : // default to gold
			ambientColor({0.2473f, 0.1995f, 0.0745f, 1.0f}),
			diffuseColor({0.7516f, 0.6065f, 0.2265f, 1.0f}),
			specularColor({0.6283f, 0.5558f, 0.2265f, 1.0f}),
			shine(51.2f) {}
	};

	namespace MATERIAL
	{
		// add more

		const Material GOLD = {
			{0.2473f, 0.1995f, 0.0745f, 1.0f},
			{0.7516f, 0.6065f, 0.2265f, 1.0f},
			{0.6283f, 0.5558f, 0.2265f, 1.0f},
			51.2f
		};
	}

	class Model : public _Entity3D
	{
	private:
		void* mGLData;
		Texture* mTexture;
		bool mHasTexture, mHasNormals;
		void recalculateMatrix() override
		{
			Mat4f rotX = constructRotateXf(this->mRotation.x);
			Mat4f rotY = constructRotateYf(this->mRotation.y); // TODO: replace with single rotation matrix;
			Mat4f rotZ = constructRotateZf(this->mRotation.z);
			Mat4f pos = constructTranslatef(this->mPosition);
			Mat4f scale = constructScalef(this->mScale);
			this->mMatrix = scale * rotX * rotY * rotZ * pos;
		}
	public:
		Vec4f color;
		Material material;
		LIGHTING lighting;

		Model(const std::string& filepath,
			  Texture* texture = nullptr,
			  LIGHTING lighting = LIGHTING::NONE, // Change to regular once finished
		      const Material& material = MATERIAL::GOLD,
			  const Vec4f& color = {0, 0, 0, 1},
			  bool hasNormals = true);
		// TODO: add more constructors

		~Model();
		Model(const Model&) = delete;

		Vec3f getDir() const override
		{
			Vec3f norm = {0, 0, 1}; // Models face positive Z
			norm.rotate(mRotation.x, mRotation.y, mRotation.z);
			return norm;
		}

		friend void render(Model& model, CustomShader* customShader);
		friend class Camera;
	};

	class Camera : public _Entity3D
	{
	private:
		Mat4f mProjMatrix;
		bool mProjNeedsRecalculation;
		float mFOV, mNear, mFar;
		void recalculateProjMatrix();
		void recalculateMatrix() override
		{
			Mat4f rotX = constructRotateXf(-this->mRotation.x);
			Mat4f rotY = constructRotateYf(-this->mRotation.y); // TODO: replace with single rotation matrix;
			Mat4f rotZ = constructRotateZf(-this->mRotation.z);
			Mat4f pos = constructTranslatef(-this->mPosition);
			Mat4f scale = constructScalef(this->mScale);
			this->mMatrix = scale * pos * rotY * rotX * rotZ;
		}
	public:
		Camera(float fov = 1.04719755f /* 60 degrees */, float zNear = 0.1f, float zFar = 1000.0f, bool bind = true);

		void setFOV(float angle) {mFOV = angle; mProjNeedsRecalculation = 1;}
		float getFOV() const {return mFOV;}
		void setNear(float zNear) {mNear = zNear; mProjNeedsRecalculation = 1;}
		float getNear() const {return mNear;}
		void setFar(float zFar) {mFar = zFar; mProjNeedsRecalculation = 1;}
		float getFar() const {return mFar;}
		void sync(const Model& model, Vec3f offset = {0, 0, 0}, bool rotation = false)
		{
			mPosition = model.mPosition + offset;
			if (rotation) mRotation = model.mRotation;
			mNeedsRecalculation = 1;
		}

		Vec3f getDir() const override
		{
			Vec3f norm = {0, 0, -1}; // Camera faces negative Z
			norm.rotate(mRotation.x, mRotation.y, mRotation.z);
			return norm;
		}

		friend void render(Model& model, CustomShader* customShader);
	};
}