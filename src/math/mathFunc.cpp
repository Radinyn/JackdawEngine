#include "../../include/JackdawMath.h"

namespace jdw
{

    double invSqrt(double x, uint8_t precision)
    {
        double y = x;
        double x2 = y * 0.5;
        int64_t i = *(int64_t*)&y;
        i = 0x5fe6eb50c7b537a9 - (i >> 1);
        y = *(double*)&i;
        for (uint8_t k = 0; k < precision; k++)
            y = y * (1.5 - (x2 * y * y));
        return y;
    }

    double lerp(double a, double b, double t)
    {
        return (a + t * (b - a));
    }

    double quadInter(double a, double b, double c, double t)
    {
        double ab = lerp(a, b, t);
        double bc = lerp(a, b, t);
        return lerp(ab, bc, t);
    }

    double cubicInter(double a, double b, double c, double d, double t)
    {
        double p = (d - c) - (a - b);
        double q = (a - b) - p;
        double r = c - a;
        return (p * t * 3) + (q * t * 2) + (r * t) + b;
    }

    double cosInter(double t)
    {
        t = -std::cos(t * PI);
        return (t + 1) / 2.0;
    }

    double smoothStep(double t)
    {
        return t * t * (3 - (2 * t));
    }

    double perlinSmoothStep(double t)
    {
        return t * t * t * ((t * ((6 * t) - 15)) + 10);
    }

    double mapValue(double value, double start1, double end1, double start2, double end2)
    {
        return start2 + ((end2 - start2) / (end1 - start1)) * (value - start1);
    }

    double degToRad(double angle)
    {
        return angle*(PI/180);
    }

	double radToDeg(double angle)
    {
        return angle*(180/PI);
    }

	double simplifyAngle(double angle)
    {
        return fmod(fmod(angle, 2*PI)+2*PI, 2*PI);
    }

    float invSqrt(float x, uint8_t precision)
    {
        float y = x;
        float x2 = y * 0.5;
        int32_t i = *(int32_t*)&y;
        i = 0x5f3759df - (i >> 1);
        y = *(float*)&i;
        for (uint8_t k = 0; k < precision; k++)
            y = y * (1.5 - (x2 * y * y));
        return y;
    }

    float lerp(float a, float b, float t)
    {
        return (a + t * (b - a));
    }

    float quadInter(float a, float b, float c, float t)
    {
        float ab = lerp(a, b, t);
        float bc = lerp(a, b, t);
        return lerp(ab, bc, t);
    }

    float cubicInter(float a, float b, float c, float d, float t)
    {
        float p = (d - c) - (a - b);
        float q = (a - b) - p;
        float r = c - a;
        return (p * t * 3) + (q * t * 2) + (r * t) + b;
    }

    float cosInter(float t)
    {
        t = -std::cos(t * PI);
        return (t + 1) / 2.0;
    }

    float smoothStep(float t)
    {
        return t * t * (3 - (2 * t));
    }

    float perlinSmoothStep(float t)
    {
        return t * t * t * ((t * ((6 * t) - 15)) + 10);
    }

    float mapValue(float value, float start1, float end1, float start2, float end2)
    {
        return start2 + ((end2 - start2) / (end1 - start1)) * (value - start1);
    }

    float degToRad(float angle)
    {
        return angle*(PI/180);
    }

	float radToDeg(float angle)
    {
        return angle*(180/PI);
    }

	float simplifyAngle(float angle)
    {
        return fmodf(fmodf(angle, 2*PI)+2*PI, 2*PI);
    }

}