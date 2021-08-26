#pragma once
#include "JackdawMath.h"

namespace jdw 
{
    class Bezier
    {
    public:
        Vec2f a1, c1, c2, a2;

        Vec2f get(double t) const;
        Vec2f getDerivative(double t) const;
    };
}