#include "../../include/JackdawCustomShader.h"
#include "shader.h"

namespace jdw
{
    CustomShader::CustomShader(const std::string& vertexShader, const std::string& geometryShader,
                                const std::string& fragmentShader, UniformMap* uniformMap)
    {
        innerShader = new Shader(vertexShader, geometryShader, fragmentShader);
        this->uniMap = uniformMap;
    }

    CustomShader::CustomShader(const std::string& vertexShader, const std::string& fragmentShader, UniformMap* uniformMap)
    {
        innerShader = new Shader(vertexShader, fragmentShader);
        this->uniMap = uniformMap;
    }

    CustomShader::~CustomShader()
    {
        delete (Shader*)innerShader;
    }
}