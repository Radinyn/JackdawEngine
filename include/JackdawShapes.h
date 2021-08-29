#pragma once
#include "JackdawMath.h"

// TODO: Add more complex shapes

namespace jdw
{
    // Shapes usable for the Polygon constructor
    namespace shapes
    {
        /* Defined in math/shapes.cpp */

        std::vector<Vec2f> rectangle(float width, float height, Vec2f start = {0, 0});
        std::vector<Vec2f> square(float a, Vec2f start = {0, 0});

        // Those two really are the same
        
        std::vector<Vec2f> regularPolygon(float radius, int numOfPoints, Vec2f center = {0, 0});
        std::vector<Vec2f> circle(float radius, int numOfPoints, Vec2f center = {0, 0});
    }
}