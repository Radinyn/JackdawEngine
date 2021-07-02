#pragma once

#include <cstdint>
#include <utility>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

/*
LIST FOR QUICK NAVIGATION:
#1 -> Math Functions
#2 -> Matrix Class
#3 -> Vector Classes
    | #3.1 Vec2
    | #3.2 Vec3
    | #3.3 Vec4
    | #3.4 Utility functions
#4 -> Matrix constructor functions
*/

namespace jdw
{
	constexpr double PI = 3.1415926536;

// o--------------------o
// | #1. Math Functions |
// o--------------------o

	double invSqrt(double x, uint8_t precision = 2);

	double lerp(double a, double b, double t);

	double quadInter(double a, double b, double c, double t);

	double cubicInter(double a, double b, double c, double d, double t);

	double cosInter(double t);

	double smoothStep(double t);

	double perlinSmoothStep(double t);

	double mapValue(double value, double start1, double end1, double start2, double end2);

	double degToRad(double angle);

	double radToDeg(double angle);

	double simplifyAngle(double angle);

	float invSqrt(float x, uint8_t precision = 2);

	float lerp(float a, float b, float t);

	float quadInter(float a, float b, float c, float t);

	float cubicInter(float a, float b, float c, float d, float t);

	float cosInter(float t);

	float smoothStep(float t);

	float perlinSmoothStep(float t);

	float mapValue(float value, float start1, float end1, float start2, float end2);

	float degToRad(float angle);

	float radToDeg(float angle);

	float simplifyAngle(float angle);

// o------------------o
// | #2. Matrix Class |
// o------------------o

template <class Numeric>
struct _Matrix4x4Type
{
    Numeric Mat[4][4];

    _Matrix4x4Type()
    {
        for (int i = 0; i < 4; i++)
            std::fill(Mat[i], Mat[i] + 4, 0);
    }

    _Matrix4x4Type(const std::vector<std::vector<Numeric>>& vec)
    {
        for (size_t i = 0; i < vec.size(); i++)
            for (size_t j = 0; j < vec[i].size(); j++)
                this->Mat[i][j] = vec[i][j];
    }

    _Matrix4x4Type(Numeric a[4][4])
    {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                this->Mat[i][j] = a[i][j];
    }

    _Matrix4x4Type(const std::initializer_list<std::initializer_list<Numeric>>& a)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                this->Mat[i][j] = ((a.begin() + i)->begin())[j];
            }
        }
    }

    _Matrix4x4Type(const _Matrix4x4Type& other)
    {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                this->Mat[i][j] = other.get(i, j);
    }

    template <class Numeric2>
    _Matrix4x4Type(const _Matrix4x4Type<Numeric2>& other)
    {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                this->Mat[i][j] = other.get(i, j);
    }

    std::string to_string() const
    {
        return
            "( " + std::to_string(this->Mat[0][0]) + ", " + std::to_string(this->Mat[0][1]) + ", " + std::to_string(this->Mat[0][2]) + ", " + std::to_string(this->Mat[0][3]) + " )\n"
            "( " + std::to_string(this->Mat[1][0]) + ", " + std::to_string(this->Mat[1][1]) + ", " + std::to_string(this->Mat[1][2]) + ", " + std::to_string(this->Mat[1][3]) + " )\n"
            "( " + std::to_string(this->Mat[2][0]) + ", " + std::to_string(this->Mat[2][1]) + ", " + std::to_string(this->Mat[2][2]) + ", " + std::to_string(this->Mat[2][3]) + " )\n"
            "( " + std::to_string(this->Mat[3][0]) + ", " + std::to_string(this->Mat[3][1]) + ", " + std::to_string(this->Mat[3][2]) + ", " + std::to_string(this->Mat[3][3]) + " )";
    }

    friend std::ostream& operator<< (std::ostream& os, const _Matrix4x4Type& mat) { os << mat.to_string(); return os; }

    Numeric get(int i, int j) const
    {
        return this->Mat[i][j];
    }

	const Numeric* getPtr() const
    {
        return &this->Mat[0][0];
    }

    Numeric* operator[] (size_t index)
    {
        return this->Mat[index];
    }

    _Matrix4x4Type& operator*= (_Matrix4x4Type other)
    {
        _Matrix4x4Type copy = *this;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                Numeric curr = 0;
                for (size_t k = 0; k < 4; k++)
                    curr += copy[i][k] * other[k][j];
                this->Mat[i][j] = curr;
            }
        }
        return *this;
    }

    _Matrix4x4Type operator* (_Matrix4x4Type other) const
    {
        _Matrix4x4Type newMat;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                Numeric curr = 0;
                for (size_t k = 0; k < 4; k++)
                    curr += this->Mat[i][k] * other[k][j];
                newMat[i][j] = curr;
            }
        }
        return newMat;
    }

    _Matrix4x4Type& operator*= (Numeric k)
    {
        _Matrix4x4Type copy = *this;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                this->Mat[i][j] *= k;
            }
        }
        return *this;
    }

    _Matrix4x4Type operator* (Numeric k) const
    {
        _Matrix4x4Type newMat;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                newMat[i][j] = this->Mat[i][j] * k;
            }
        }
        return newMat;
    }

    _Matrix4x4Type& operator+= (_Matrix4x4Type other)
    {
        _Matrix4x4Type copy = *this;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                this->Mat[i][j] += other[i][j];
            }
        }
        return *this;
    }

    _Matrix4x4Type operator+ (_Matrix4x4Type other) const
    {
        _Matrix4x4Type newMat;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                newMat[i][j] = this->Mat[i][j] + other[i][j];
            }
        }
        return newMat;
    }

    _Matrix4x4Type& operator-= (_Matrix4x4Type other)
    {
        _Matrix4x4Type copy = *this;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                this->Mat[i][j] -= other[i][j];
            }
        }
        return *this;
    }

    _Matrix4x4Type operator- (_Matrix4x4Type other) const
    {
        _Matrix4x4Type newMat;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                newMat[i][j] = this->Mat[i][j] - other[i][j];
            }
        }
        return newMat;
    }

    _Matrix4x4Type operator- () const
    {
        _Matrix4x4Type newMat;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                newMat[i][j] = -this->Mat[i][j];
            }
        }
        return newMat;
    }

    _Matrix4x4Type operator+ () const
    {
        _Matrix4x4Type newMat = *this;
        return newMat;
    }

    bool operator== (_Matrix4x4Type other) const
    {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                if (this->Mat[i][j] != other[i][j]) return false;
        return true;
    }

    bool operator!= (_Matrix4x4Type other) const
    {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                if (this->Mat[i][j] != other[i][j]) return true;
        return false;
    }

    _Matrix4x4Type& transpose()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                std::swap(this->Mat[i][j], this->Mat[j][i]);
            }
        }
        return *this;
    }

    _Matrix4x4Type transposed() const
    {
        _Matrix4x4Type newMat;
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                newMat[j][i] = this->Mat[i][j];
                newMat[i][j] = this->Mat[j][i];
            }
        }
        return newMat;
    }

};

typedef _Matrix4x4Type<float> Mat4f;
typedef _Matrix4x4Type<double> Mat4d;
typedef _Matrix4x4Type<int32_t> Mat4i;
typedef _Matrix4x4Type<int64_t> Mat4ll;
typedef _Matrix4x4Type<uint32_t> Mat4ui;
typedef _Matrix4x4Type<uint64_t> Mat4ull;

// o--------------------o
// | #3. Vector Classes |
// o--------------------o

/// #3.1 Vec2 ///

template <class Numeric>
struct _Vector2Type
{
	Numeric x, y;

	_Vector2Type(Numeric x = 0, Numeric y = 0) :
		x(x), y(y) {}

	_Vector2Type(const _Vector2Type& other) :
		x(other.x), y(other.y) {}

	template <class Numeric2>
	_Vector2Type(const _Vector2Type<Numeric2>& other) :
		x(other.x), y(other.y) {}

	_Vector2Type(const std::pair<Numeric, Numeric>& pair) :
		x(pair.first), y(pair.first) {}

	double mag() const { return std::sqrt((double)this->x * this->x + this->y * this->y); }
	double mag2() const { return ((double)this->x * this->x + this->y * this->y); }
	double dot(const  _Vector2Type& other) const { return ((double)this->x * other.x + this->y * other.y); }
	double cross(const  _Vector2Type& other) const { return (this->x * other.y - this->y * other.x); }
	std::string to_string() const { return "( " + std::to_string(this->x) + ", " + std::to_string(this->y) + " )"; }
	friend std::ostream& operator<< (std::ostream& os, const _Vector2Type& vec) { os << vec.to_string(); return os; }

	_Vector2Type& normalize()
	{
		Numeric inv = invSqrt(this->mag2());
		this->x *= inv;
		this->y *= inv;
		return *this;
	}

	_Vector2Type normalized() const
	{
		Numeric inv = invSqrt(this->mag2());
		return { this->x * inv, this->y * inv };
	}

	_Vector2Type& rotate(double angle)
	{
		Numeric currX = this->x, currY = this->y;
		double cosine = std::cos(angle), sine = std::sin(angle);
		this->x = currX * cosine - currY * sine;
		this->y = currX * sine + currY * cosine;
		return *this;
	}

	_Vector2Type rotated(double angle) const
	{
		double cosine = std::cos(angle), sine = std::sin(angle);
		return { this->x * cosine - this->y * sine, this->x * sine + this->y * cosine };
	}

	double getAngle() const
	{
		if ((!this->y) && (!this->x)) return 0;
		double angle = std::atan2(this->y, this->x);
		if (angle < 0) angle += 2 * PI;
		return angle;
	}

	double getAngle(_Vector2Type& other) const
	{
		if ((!this->y) && (!this->x)) return 0;
		if ((!other.y) && (!other.x)) return 0;
		double cos_angle = this->dot(other) * invSqrt(this->mag2() * other.mag2());
		cos_angle = std::max(std::min(cos_angle, 1.0), -1.0);
		return std::acos(cos_angle);
	}

	_Vector2Type operator+ (const _Vector2Type& right) const
	{
		return { this->x + right.x, this->y + right.y };
	}

	_Vector2Type& operator+= (const _Vector2Type& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	_Vector2Type operator- (const _Vector2Type& right) const
	{
		return { this->x - right.x, this->y - right.y };
	}

	_Vector2Type& operator-= (const _Vector2Type& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	_Vector2Type operator* (const Numeric k) const
	{
		return { this->x * k, this->y * k };
	}

	_Vector2Type& operator*= (const Numeric k)
	{
		this->x *= k;
		this->y *= k;
		return *this;
	}

	_Vector2Type operator/ (const Numeric k) const
	{
		return { this->x / k, this->y / k };
	}

	_Vector2Type& operator/= (const Numeric k)
	{
		this->x /= k;
		this->y /= k;
		return *this;
	}

	_Vector2Type operator+ () const { return { +this->x, +this->y }; }
	_Vector2Type operator- () const { return { -this->x, -this->y }; }

	bool operator== (const _Vector2Type& right) const
	{
		return ((this->x == right.x) && (this->y == right.y));
	}

	bool operator!= (const _Vector2Type& right) const
	{
		return ((this->x != right.x) || (this->y != right.y));
	}

};

typedef _Vector2Type<float> Vec2f;
typedef _Vector2Type<double> Vec2d;
typedef _Vector2Type<int32_t> Vec2i;
typedef _Vector2Type<int64_t> Vec2ll;
typedef _Vector2Type<uint32_t> Vec2ui;
typedef _Vector2Type<uint64_t> Vec2ull;

/// #3.2 Vec3 ///

template <class Numeric>
struct _Vector3Type
{
	Numeric x = 0, y = 0, z = 0;

	_Vector3Type(Numeric x = 0, Numeric y = 0, Numeric z = 0) :
		x(x), y(y), z(z) {}

	_Vector3Type(const _Vector3Type& other) :
		x(other.x), y(other.y), z(other.z) {}

	template <class Numeric2>
	_Vector3Type(const _Vector3Type<Numeric2>& other) :
		x(other.x), y(other.y), z(other.z) {}

	_Vector3Type(const _Vector2Type<Numeric>& other) :
		x(other.x), y(other.y), z(0) {}

	double mag() const { return std::sqrt((double)this->x * this->x + (double)this->y * (double)this->y + this->z * this->z); }
	double mag2() const { return ((double)this->x * this->x + (double)this->y * this->y + (double)this->z * this->z); }
	double dot(const _Vector3Type& other) const { return ((double)this->x * other.x + (double)this->y * other.y + (double)this->z * other.z); }
	_Vector3Type cross(const _Vector3Type& other) const { return _Vector3Type(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x); }
	std::string to_string() const { return "( " + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + " )"; }
	friend std::ostream& operator<< (std::ostream& os, const _Vector3Type& vec) { os << vec.to_string(); return os; }

	_Vector3Type& normalize()
	{
		Numeric inv = invSqrt(this->mag2());
		this->x *= inv;
		this->y *= inv;
		this->z *= inv;
		return *this;
	}

	_Vector3Type normalized() const
	{
		Numeric inv = invSqrt(this->mag2());
		return { this->x * inv, this->y * inv, this->z * inv };
	}

	_Vector3Type& rotate(double angleX = 0, double angleY = 0, double angleZ = 0)
	{
		Numeric currX = this->x, currY = this->y, currZ = this->z;

		const double cosX = std::cos(angleX), sinX = std::sin(angleX);
		const double cosY = std::cos(angleY), sinY = std::sin(angleY);
		const double cosZ = std::cos(angleZ), sinZ = std::sin(angleZ);

		this->x = (cosZ * cosY) * currX + (cosZ * sinY * sinX - sinZ * cosX) * currY + (cosZ * sinY * cosX - sinZ * sinX) * currZ;
		this->y = (sinZ * cosY) * currX + (sinZ * sinY * sinX + cosZ * cosX) * currY + (sinZ * sinY * cosX - cosZ * sinX) * currZ;
		this->z = ((-1) * sinY) * currX + (cosY * sinX) * currY + (cosY * cosX) * currZ;
		return *this;
	}

	_Vector3Type rotated(double angleX = 0, double angleY = 0, double angleZ = 0) const
	{
		const double cosX = std::cos(angleX), sinX = std::sin(angleX);
		const double cosY = std::cos(angleY), sinY = std::sin(angleY);
		const double cosZ = std::cos(angleZ), sinZ = std::sin(angleZ);

		return {
			(cosZ * cosY) * this->x + (cosZ * sinY * sinX - sinZ * cosX) * this->y + (cosZ * sinY * cosX - sinZ * sinX) * this->z,
			(sinZ * cosY) * this->x + (sinZ * sinY * sinX + cosZ * cosX) * this->y + (sinZ * sinY * cosX - cosZ * sinX) * this->z,
			((-1) * sinY) * this->x + (cosY * sinX) * this->y + (cosY * cosX) * this->z
		};
	}

	double getAngle(const _Vector3Type& other = _Vector3Type(1, 0, 0)) const
	{
		if ((!this->y) && (!this->x) && (!this->z)) return 0;
		if ((!other.y) && (!other.x) && (!other.z)) return 0;

		double cos_angle = this->dot(other) * invSqrt(this->mag2() * other.mag2());
		cos_angle = std::max(std::min(cos_angle, 1.0), -1.0);
		return std::acos(cos_angle);
	}

	// Get a std::pair of angles from the (1, 0, 0) vector
	std::pair<double, double> getAngles(const _Vector3Type& other = _Vector3Type(1, 0, 0)) const
	{
		if ((!this->y) && (!this->x) && (!this->z)) return { 0, 0 };
		if ((!other.y) && (!other.x) && (!other.z)) return { 0, 0 };

		double cos_angle;

		_Vector2Type<Numeric> noZ1 = { this->x, this->y };
		_Vector2Type<Numeric> noZ2 = { other.x, other.y };
		_Vector2Type<Numeric> noY1 = { this->x, this->z };
		_Vector2Type<Numeric> noY2 = { other.x, other.z };

		cos_angle = noZ1.dot(noZ2) * invSqrt(noZ1.mag2() * noZ2.mag2());
		cos_angle = std::max(std::min(cos_angle, 1.0), -1.0);
		double angleXY = std::acos(cos_angle);

		cos_angle = noY1.dot(noY2) * invSqrt(noY1.mag2() * noY2.mag2());
		cos_angle = std::max(std::min(cos_angle, 1.0), -1.0);
		double angleXZ = std::acos(cos_angle);

		return { angleXY, angleXZ };
	}

	_Vector3Type operator+ (const _Vector3Type& right) const
	{
		return { this->x + right.x, this->y + right.y, this->z + right.z };
	}

	_Vector3Type& operator+= (const _Vector3Type& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	_Vector3Type operator- (const _Vector3Type& right) const
	{
		return { this->x - right.x, this->y - right.y, this->z - right.z };
	}

	_Vector3Type& operator-= (const _Vector3Type& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	_Vector3Type operator* (Numeric k) const
	{
		return { this->x * k, this->y * k, this->z * k };
	}

	_Vector3Type& operator*= (Numeric k)
	{
		this->x *= k;
		this->y *= k;
		this->z *= k;
		return *this;
	}

	_Vector3Type operator/ (Numeric k) const
	{
		return { this->x / k, this->y / k, this->z / k };
	}

	_Vector3Type& operator/= (Numeric k)
	{
		this->x /= k;
		this->y /= k;
		this->z /= k;
		return *this;
	}

	bool operator== (const _Vector3Type& right) const
	{
		return ((this->x == right.x) && (this->y == right.y) && (this->z == right.z));
	}

	bool operator!= (const _Vector3Type& right) const
	{
		return ((this->x != right.x) || (this->y != right.y) || (this->z != right.z));
	}

	_Vector3Type operator+ () const { return { +this->x, +this->y, +this->z }; }
	_Vector3Type operator- () const { return { -this->x, -this->y, -this->z }; }

	_Vector3Type operator* (_Matrix4x4Type<Numeric>& mat) const
	{
		Numeric a, b, c, w;
		a = mat[0][0] * this->x + mat[1][0] * this->y + mat[2][0] * this->z + mat[3][0];
		b = mat[0][1] * this->x + mat[1][1] * this->y + mat[2][1] * this->z + mat[3][1];
		c = mat[0][2] * this->x + mat[1][2] * this->y + mat[2][2] * this->z + mat[3][2];
		w = mat[0][3] * this->x + mat[1][3] * this->y + mat[2][3] * this->z + mat[3][3];

		if ((w != 1) && (w))
		{
			a /= w;
			b /= w;
			c /= w;
		}
		return { a, b, c };
	}

	_Vector3Type& operator*= (_Matrix4x4Type<Numeric>& mat)
	{
		Numeric currX = this->x, currY = this->y, currZ = this->z;
		this->x = mat[0][0] * currX + mat[1][0] * currX + mat[2][0] * currX + mat[3][0];
		this->y = mat[0][1] * currY + mat[1][1] * currY + mat[2][1] * currY + mat[3][1];
		this->z = mat[0][2] * currZ + mat[1][2] * currZ + mat[2][2] * currZ + mat[3][2];
		Numeric w = this->z = mat[0][3] * currZ + mat[1][3] * currZ + mat[2][3] * currZ + mat[3][3];

		if ((w != 1) && (w))
		{
			this->x /= w;
			this->y /= w;
			this->z /= w;
		}

		return *this;
	}

};

typedef _Vector3Type<float> Vec3f;
typedef _Vector3Type<double> Vec3d;
typedef _Vector3Type<int32_t> Vec3i;
typedef _Vector3Type<int64_t> Vec3ll;
typedef _Vector3Type<uint32_t> Vec3ui;
typedef _Vector3Type<uint64_t> Vec3ull;

/// #3.3 Vec4 ///

template <class Numeric>
struct _Vector4Type
{
	union
	{
		Numeric x;
		Numeric r;
	};
	union
	{
		Numeric y;
		Numeric g;
	};
	union
	{
		Numeric z;
		Numeric b;
	};
	union
	{
		Numeric w;
		Numeric a;
	};

	_Vector4Type(Numeric x = 0, Numeric y = 0, Numeric z = 0, Numeric w = 1) :
		x(x), y(y), z(z), w(w) {}

	_Vector4Type(const _Vector4Type& other) :
		x(other.x), y(other.y), z(other.z), w(other.w) {}

	template <class Numeric2>
	_Vector4Type(const _Vector4Type<Numeric2>& other) :
		x(other.x), y(other.y), z(other.z), w(other.w) {}

	std::string to_string() const {
		return "( " + std::to_string(this->x) + ", " + std::to_string(this->y) + ", "
			+ std::to_string(this->z) + ", " + std::to_string(this->w) + " )";
	}
	friend std::ostream& operator<< (std::ostream& os, const _Vector4Type& vec) { os << vec.to_string(); return os; }

	_Vector4Type operator+ (const _Vector4Type& right) const
	{
		return { this->x + right.x, this->y + right.y, this->z + right.z, this->w + right.w };
	}

	_Vector4Type& operator+= (const _Vector4Type& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;
		return *this;
	}

	_Vector4Type operator- (const _Vector4Type& right) const
	{
		return { this->x - right.x, this->y - right.y, this->z - right.z, this->w - right.w };
	}

	_Vector4Type& operator-= (const _Vector4Type& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		this->w -= other.w;
		return *this;
	}

	_Vector4Type operator* (Numeric k) const
	{
		return { this->x * k, this->y * k, this->z * k, this->w * k };
	}

	_Vector4Type& operator*= (Numeric k)
	{
		this->x *= k;
		this->y *= k;
		this->z *= k;
		this->w *= k;
		return *this;
	}

	_Vector4Type operator/ (Numeric k) const
	{
		return { this->x / k, this->y / k, this->z / k, this->w / k };
	}

	_Vector4Type& operator/= (Numeric k)
	{
		this->x /= k;
		this->y /= k;
		this->z /= k;
		this->w /= k;
		return *this;
	}

	bool operator== (const _Vector4Type& right) const
	{
		return ((this->x == right.x) && (this->y == right.y) && (this->z == right.z) && (this->w == right.w));
	}

	bool operator!= (const _Vector4Type& right) const
	{
		return ((this->x != right.x) || (this->y != right.y) || (this->z != right.z) || (this->w != right.w));
	}

	_Vector4Type operator+ () const { return { +this->x, +this->y, +this->z, +this->w }; }
	_Vector4Type operator- () const { return { -this->x, -this->y, -this->z, +this->w }; }
};

typedef _Vector4Type<float> Vec4f;
typedef _Vector4Type<double> Vec4d;
typedef _Vector4Type<int32_t> Vec4i;
typedef _Vector4Type<int64_t> Vec4ll;
typedef _Vector4Type<uint32_t> Vec4ui;
typedef _Vector4Type<uint64_t> Vec4ull;

/// #3.4 Vector utility functions /// 

template <class Numeric>
double dist(const _Vector2Type<Numeric>& a, const _Vector2Type<Numeric>& b)
{
	return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

template <class Numeric>
double dist2(const _Vector2Type<Numeric>& a, const _Vector2Type<Numeric>& b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

template <class Numeric>
double dist(const _Vector3Type<Numeric>& a, const _Vector3Type<Numeric>& b)
{
	return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

template <class Numeric>
double dist2(const _Vector3Type<Numeric>& a, const _Vector3Type<Numeric>& b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

template <class Numeric>
_Vector2Type<Numeric> lerp(const _Vector2Type<Numeric> a, const _Vector2Type<Numeric> b, double t = 0.2)
{
	return _Vector2Type<Numeric>(lerp(a.x, b.x), lerp(a.y, b.y));
}

template <class Numeric>
_Vector3Type<Numeric> lerp(const _Vector3Type<Numeric> a, const _Vector3Type<Numeric> b, double t = 0.2)
{
	return _Vector3Type<Numeric>(lerp(a.x, b.x), lerp(a.y, b.y), lerp(a.z, b.z));
}

// o----------------------------------o
// | #4. Matrix constructor functions |
// o----------------------------------o

// left, right, bottom, top, near, far
template <class Numeric>
_Matrix4x4Type<Numeric> constructOrtho(Numeric l, Numeric r, Numeric b, Numeric t, Numeric n, Numeric f)
{
	return {
	{ 2 / (r - l), 0, 0,  0 },
	{ 0, 2 / (t - b), 0,  0 },
	{ 0, 0, -2 / (f - n), 0 },
	{ -(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n), 1 }
	};
}

constexpr auto constructOrthof = &constructOrtho<float>;
constexpr auto constructOrthod = &constructOrtho<double>;

// aspect ratio,  field of view (radians), near, far   
template <class Numeric>
_Matrix4x4Type<Numeric> constructPersp(Numeric a, Numeric fov, Numeric zNear, Numeric zFar)
{
	fov = 1 / std::tan(fov / 2);
	return {
		{ fov / a, 0, 0, 0 },
		{ 0, fov, 0, 0 },
		{ 0, 0, (zNear + zFar) / (zNear - zFar), -1},
		{ 0, 0, (2 * zFar * zNear) / (zNear - zFar), 0}
	};
}

constexpr auto constructPerspf = &constructPersp<float>;
constexpr auto constructPerspd = &constructPersp<double>;

template <class Numeric>
_Matrix4x4Type<Numeric> constructLookAt(const _Vector3Type<Numeric>& eye, const _Vector3Type<Numeric>& at, const _Vector3Type<Numeric>& up)
{
	_Vector3Type<Numeric> axisZ = at - eye;
	axisZ.normalize();

	_Vector3Type<Numeric> axisX = axisZ.cross(up);
	axisX.normalize();

	_Vector3Type<Numeric> axisY = axisX.cross(axisZ);

	axisZ = -axisZ;

	_Matrix4x4Type<Numeric> matrix = {
		{ axisX.x, axisX.y, axisX.z, 0 },
		{ axisY.x, axisY.y, axisY.z, 0 },
		{ axisZ.x, axisZ.y, axisZ.z, 0 },
		{ (Numeric)-axisX.dot(eye) , (Numeric)-axisY.dot(eye), (Numeric)-axisZ.dot(eye), 1 }
	};

	return matrix;
}

constexpr auto constructLookAtf = &constructLookAt<float>;
constexpr auto constructLookAtd = &constructLookAt<double>;

template <class Numeric>
_Matrix4x4Type<Numeric> constructTranslate(const _Vector3Type<Numeric>& vec)
{
	return {
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ vec.x, vec.y, vec.z, 1}
	};
}

constexpr auto constructTranslatef = &constructTranslate<float>;
constexpr auto constructTranslated = &constructTranslate<double>;
constexpr auto constructTranslatei = &constructTranslate<int32_t>;
constexpr auto constructTranslatell = &constructTranslate<int64_t>;
constexpr auto constructTranslateui = &constructTranslate<uint32_t>;
constexpr auto constructTranslateull = &constructTranslate<uint64_t>;

template <class Numeric>
_Matrix4x4Type<Numeric> constructScale(const _Vector3Type<Numeric>& vec)
{
	return {
	{ vec.x, 0, 0, 0 },
	{ 0, vec.y, 0, 0 },
	{ 0, 0, vec.z, 0 },
	{ 0, 0, 0, 1 }
	};
}

constexpr auto constructScalef = &constructScale<float>;
constexpr auto constructScaled = &constructScale<double>;
constexpr auto constructScalei = &constructScale<int32_t>;
constexpr auto constructScalell = &constructScale<int64_t>;
constexpr auto constructScaleui = &constructScale<uint32_t>;
constexpr auto constructScaleull = &constructScale<uint64_t>;

template <class Numeric>
_Matrix4x4Type<Numeric> constructRotateX(Numeric angle)
{
	Numeric cosine = (Numeric)std::cos(angle);
	Numeric sine = (Numeric)std::sin(angle);
	return {
	{ 1, 0, 0, 0 },
	{ 0, cosine, sine, 0 },
	{ 0, -sine, cosine, 0 },
	{ 0, 0, 0, 1}
	};
}

constexpr auto constructRotateXf = &constructRotateX<float>;
constexpr auto constructRotateXd = &constructRotateX<double>;

template <class Numeric>
_Matrix4x4Type<Numeric> constructRotateY(Numeric angle)
{
	Numeric cosine = (Numeric)std::cos(angle);
	Numeric sine = (Numeric)std::sin(angle);
	return {
	{ cosine, 0, -sine, 0 },
	{ 0, 1, 0, 0 },
	{ sine, 0, cosine, 0 },
	{ 0, 0, 0, 1}
	};
}

constexpr auto constructRotateYf = &constructRotateY<float>;
constexpr auto constructRotateYd = &constructRotateY<double>;

template <class Numeric>
_Matrix4x4Type<Numeric> constructRotateZ(Numeric angle)
{
	Numeric cosine = (Numeric)std::cos(angle);
	Numeric sine = (Numeric)std::sin(angle);
	return {
	{ cosine, sine, 0, 0 },
	{ -sine, cosine, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1}
	};
}

constexpr auto constructRotateZf = &constructRotateZ<float>;
constexpr auto constructRotateZd = &constructRotateZ<double>;

template <class Numeric>
_Matrix4x4Type<Numeric> constructIdentity()
{
	return {
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 }
	};
}

constexpr auto constructIdentityf = &constructIdentity<float>;
constexpr auto constructIdentityd = &constructIdentity<double>;
constexpr auto constructIdentityi = &constructIdentity<int32_t>;
constexpr auto constructIdentityll = &constructIdentity<int64_t>;
constexpr auto constructIdentityui = &constructIdentity<uint32_t>;
constexpr auto constructIdentityull = &constructIdentity<uint64_t>;

}