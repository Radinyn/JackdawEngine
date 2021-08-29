#include "../../include/JackdawShapes.h"

namespace jdw
{
    namespace shapes
    {
        std::vector<Vec2f> rectangle(float width, float height, Vec2f start)
        {
            return {start, start + Vec2f(width, 0), start + Vec2f(width, height), start + Vec2f(0, height)};
        }

        std::vector<Vec2f> square(float a, Vec2f start)
        {
            return rectangle(a, a, start);
        }

        std::vector<Vec2f> regularPolygon(float radius, int numOfPoints, Vec2f center)
        {
            std::vector<Vec2f> points(numOfPoints);
            Vec2f vec = {radius, 0};
            double angle = (PI*2)/numOfPoints;

            for (int i = 0; i < numOfPoints; i++)
            {
                points[i] = center+vec;
                vec.rotate(angle);
            }

            return points;
        }

        std::vector<Vec2f> circle(float radius, int numOfPoints, Vec2f center)
        {
            return regularPolygon(radius, numOfPoints, center);
        }
    }
}