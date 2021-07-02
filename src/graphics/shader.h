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
	Shader(const std::string& shader);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform(const std::string& name, int v);
	void setUniform(const std::string& name, const jdw::Mat4f& mat);

	int getUniformLocation(const std::string& name);

};