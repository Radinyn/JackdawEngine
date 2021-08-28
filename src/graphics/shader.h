#pragma once
#include <string>
#include <unordered_map>
#include "../../include/JackdawMath.h"

class Shader
{
private:
	unsigned int mID;
	std::unordered_map<std::string, int> mUniformCache;

public:
	Shader(const std::string& shader, bool hasGeometryShader = false);
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	Shader(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform(const std::string& name, float v0);
	void setUniform(const std::string& name, const jdw::Vec2f& vec);
	void setUniform(const std::string& name, const jdw::Vec3f& vec);
	void setUniform(const std::string& name, const jdw::Vec4f& vec);
	void setUniform(const std::string& name, int v0);
	void setUniform(const std::string& name, const jdw::Vec2i& vec);
	void setUniform(const std::string& name, const jdw::Vec3i& vec);
	void setUniform(const std::string& name, const jdw::Vec4i& vec);
	void setUniform(const std::string& name, unsigned int v0);
	void setUniform(const std::string& name, const jdw::Vec2ui& vec);
	void setUniform(const std::string& name, const jdw::Vec3ui& vec);
	void setUniform(const std::string& name, const jdw::Vec4ui& vec);
	void setUniform(const std::string& name, const jdw::Mat4f& mat);

	int getUniformLocation(const std::string& name);

};