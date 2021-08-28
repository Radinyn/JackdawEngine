#pragma once
#include "JackdawMath.h"
#include <unordered_map>
#include <utility>
#include <variant>

namespace jdw
{
    typedef std::variant<
    int, Vec2i, Vec3i, Vec4i,
    unsigned int, Vec2ui, Vec3ui, Vec4ui,
    float, Vec2f, Vec3f, Vec4f,
    Mat4f> UniformValue;

    typedef std::unordered_map<std::string, UniformValue> UniformMap;

    struct CustomShader
    {
        UniformMap* uniMap;
        void* innerShader;

        CustomShader(const std::string& vertexShader, const std::string& geometryShader,
                    const std::string& fragmentShader, UniformMap* uniformMap = nullptr);
        CustomShader(const std::string& vertexShader, const std::string& fragmentShader, UniformMap* uniformMap = nullptr);
        ~CustomShader();
    };
}