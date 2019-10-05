#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <chrono>
#include <ctime>
#include <random>
#include "stdlib.h"

using namespace std;
#define pi 3.14159
static thread_local uint32_t s_RndState = 1;

static uint32_t XorShift32()
{
    uint32_t x = s_RndState + 1;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 15;
    s_RndState = x;
    return x;
}

static float RandomFloat01() //Same random each time
{
	return (XorShift32() & 0xFFFFFF) / 16777216.0f;
}

static float RandomFloat02(int start, int end) //Different random each time
{
	std::random_device r;
	std::seed_seq seed{ r() };
	std::mt19937 eng{ seed };

	std::uniform_real_distribution<> distReal(start, end);
	return (float)distReal(eng);
}

struct Timer
{
	std::chrono::high_resolution_clock::time_point start, end;

	std::chrono::duration<float> duration;

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << "Duration: " << duration.count() << std::endl;
	}
};

template<typename T>
class Vec2
{
public:
	Vec2() : x(0), y(0) {}
	Vec2(T xx) : x(xx), y(xx) {}
	Vec2(T xx, T yy) : x(xx), y(yy) {}
	Vec2 operator + (const Vec2 &v) const
	{
		return Vec2(x + v.x, y + v.y);
	}
	Vec2 operator / (const T &r) const
	{
		return Vec2(x / r, y / r);
	}
	Vec2 operator * (const T &r) const
	{
		return Vec2(x * r, y * r);
	}
	Vec2& operator /= (const T &r)
	{
		x /= r, y /= r; return *this;
	}
	Vec2& operator *= (const T &r)
	{
		x *= r, y *= r; return *this;
	}
	friend std::ostream& operator << (std::ostream &s, const Vec2<T> &v)
	{
		return s << '[' << v.x << ' ' << v.y << ']';
	}
	friend Vec2 operator * (const T &r, const Vec2<T> &v)
	{
		return Vec2(v.x * r, v.y * r);
	}
	T x, y;
};

template<typename T>
class Vec3
{
public:
	Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
	Vec3(T xx) : x(xx), y(xx), z(xx) {}
	Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
	Vec3 operator + (const Vec3 &v) const
	{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}
	Vec3 operator - (const Vec3 &v) const
	{
		return Vec3(x - v.x, y - v.y, z - v.z);
	}
	Vec3 operator - () const
	{
		return Vec3(-x, -y, -z);
	}
	Vec3 operator * (const T &r) const
	{
		return Vec3(x * r, y * r, z * r);
	}
	Vec3 operator * (const Vec3 &v) const
	{
		return Vec3(x * v.x, y * v.y, z * v.z);
	}
	T dotProduct(const Vec3<T> &v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
	Vec3& operator /= (const T &r)
	{
		x /= r, y /= r, z /= r; return *this;
	}
	Vec3& operator *= (const T &r)
	{
		x *= r, y *= r, z *= r; return *this;
	}
	Vec3 crossProduct(const Vec3<T> &v) const
	{
		return Vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	T norm() const
	{
		return x * x + y * y + z * z;
	}
	T length() const
	{
		return sqrt(norm());
	}
	const T& operator [] (uint8_t i) const { return (&x)[i]; }
	T& operator [] (uint8_t i) { return (&x)[i]; }
	Vec3& normalize()
	{
		T n = norm();
		if (n > 0) {
			T factor = 1 / sqrt(n);
			x *= factor, y *= factor, z *= factor;
		}

		return *this;
	}

	friend Vec3 operator * (const T &r, const Vec3 &v)
	{
		return Vec3<T>(v.x * r, v.y * r, v.z * r);
	}
	friend Vec3 operator / (const T &r, const Vec3 &v)
	{
		return Vec3<T>(r / v.x, r / v.y, r / v.z);
	}

	friend std::ostream& operator << (std::ostream &s, const Vec3<T> &v)
	{
		return s << '[' << v.x << ' ' << v.y << ' ' << v.z << ']';
	}

	T x, y, z;
};

struct Vector2
{
	//Vector2(){};
	Vector2() //Constructor
	{
		this->x = 0.0f;
		this->y = 0.0f;

	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	};
	float x, y;

	Vector2 operator+(const Vector2& vecObj) //Addition operator vector+vector
	{
		return Vector2
		(
			x + vecObj.x,
			y + vecObj.y
		);
	}

	Vector2 operator-(const Vector2& vecObj) //Subtraction operator vector-vector
	{
		return Vector2
		(
			x - vecObj.x,
			y - vecObj.y
		);
	}

	Vector2 operator*(float n)
	{
		return Vector2
		(
			x * n,
			y * n
		);
	}
};

struct Vector3
{
	float x, y, z;

	Vector3() //Constructor
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	Vector3(float x, float y, float z) //Constructor with values
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3(float x, float y, float z, float w) //Constructor with values
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3(float val) //Sets all vector values to val
	{
		this->x = val;
		this->y = val;
		this->z = val;
	}

	void Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float Length() //Vector length
	{
		return sqrt
		(
			x * x + 
			y * y + 
			z * z
		);
	}

	Vector3 Normalize() //Normalize Vector
	{
		return (*this) * (1.0f / Length());
	}

	float& operator[](const int index)
	{
		return *(&(this->x) + index);
	}

	void operator=(const Vector3& vecObj)
	{
		this->x = vecObj.x;
		this->y = vecObj.y;
		this->z = vecObj.z;
	}

	Vector3 operator+(const Vector3& vecObj) //Addition operator vector+vector
	{
		return Vector3
		(
			x + vecObj.x, 
			y + vecObj.y, 
			z + vecObj.z
		);
	}

	Vector3 operator-(const Vector3& vecObj) //Subtraction operator vector-vector
	{
		return Vector3
		(
			x - vecObj.x, 
			y - vecObj.y, 
			z - vecObj.z
		);
	}

	Vector3 operator*(float n)
	{
		return Vector3
		(
			x * n, 
			y * n, 
			z * n
		);
	}

	Vector3 operator*(Vector3 vecObj)
	{
		return Vector3
		(
			x * vecObj.x, 
			y * vecObj.y, 
			z * vecObj.z
		);
	}

	Vector3 operator/(float n)
	{
		return Vector3
		(
			x / n, 
			y / n, 
			z / n
		);
	}

	float Dot(Vector3 vecObj) //Dot product
	{
		return 	
		(
			x * vecObj.x + 
			y * vecObj.y + 
			z * vecObj.z
		);
	}

	static float StaticDot(Vector3 vec1, Vector3 vec2) //Dot product
	{
		return 	
		(
			vec1.x * vec2.x + 
			vec1.y * vec2.y + 
			vec1.z * vec2.z
		);
	}

	static Vector3 Cross(Vector3 vec1, Vector3 vec2) //Cross product
	{
		return Vector3
		(
			vec1.y * vec2.z - vec1.z * vec2.y,
			-(vec1.x * vec2.z - vec1.z * vec2.x),
			vec1.x * vec2.y - vec1.y * vec2.x
		);
	}
	// static Vector3 Cross(Vector3 vec1, Vector3 vec2) //Cross product
	// {
	// 	return Vector3
	// 	(
	// 		y * vecObj.z - z * vecObj.y,
	// 		x * vecObj.z - z * vecObj.x,
	// 		x * vecObj.y - y * vecObj.x
	// 	);
	// }
};

struct iVector4
{
	iVector4(){};
	iVector4(int x, int y, int z, int w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	};
	int x, y, z, w;
};

class Vector4
{

  private:

  public:
	float vect[4];
	friend class MatrixLib4D;

	Vector4() //Constructor
	{
		vect[0] = 0.0f;
		vect[1] = 0.0f;
		vect[2] = 0.0f;
		vect[3] = 1.0f;
	}

	Vector4(float x, float y, float z) //Constructor with values
	{
		vect[0] = x;
		vect[1] = y;
		vect[2] = z;
		vect[3] = 1.0f;
	}

	Vector4(float x, float y, float z, float w) //Constructor with values
	{
		vect[0] = x;
		vect[1] = y;
		vect[2] = z;
		vect[3] = w;
	}

	Vector4(float val) //Sets all vector values to val
	{
		vect[0] = val;
		vect[1] = val;
		vect[2] = val;
		vect[3] = 1.0f;
	}

	float GetVectorValueByIndex(int n)
	{
		return vect[n];
	}

	void SetVect(float x, float y, float z, float w)
	{
		vect[0] = x;
		vect[1] = y;
		vect[2] = z;
		vect[3] = w;
	}

	float VectLength() //Vector length
	{
		return sqrt(vect[0] * vect[0] + vect[1] * vect[1] + vect[2] * vect[2]);
	}

	Vector4 VectNorm() //Normalize Vector
	{
		Vector4 newObject = (*this) * (1.0f / VectLength());
		return (newObject);
	}

	float &operator[](const int index)
	{
		return vect[index];
	}

	void operator=(const Vector4& vecObj)
	{
		vect[0] = vecObj.vect[0];
		vect[1] = vecObj.vect[1];
		vect[2] = vecObj.vect[2];
		vect[3] = vecObj.vect[3];
	}

	Vector4 operator+(const Vector4& vecObj) //Addition operator vector+vector
	{
		Vector4 newObject;
		newObject.vect[0] = vect[0] + vecObj.vect[0];
		newObject.vect[1] = vect[1] + vecObj.vect[1];
		newObject.vect[2] = vect[2] + vecObj.vect[2];
		return (newObject);
	}

	Vector4 operator-(const Vector4& vecObj) //Subtraction operator vector-vector
	{
		Vector4 newObject;
		newObject.vect[0] = vect[0] - vecObj.vect[0];
		newObject.vect[1] = vect[1] - vecObj.vect[1];
		newObject.vect[2] = vect[2] - vecObj.vect[2];
		return (newObject);
	}

	Vector4 operator*(float n)
	{
		return Vector4(vect[0] * n, vect[1] * n, vect[2] * n);
	}

	static Vector4 MultiplyVectors(Vector4 vec1, Vector4 vec2)
	{
		Vector4 newObject;
		newObject.vect[0] = vec1[0] * vec2[0];
		newObject.vect[1] = vec1[1] * vec2[1];
		newObject.vect[2] = vec1[2] * vec2[2];
		return (newObject);
	}

	Vector4 operator/(float n)
	{
		Vector4 newObject;
		newObject.vect[0] = vect[0] / n;
		newObject.vect[1] = vect[1] / n;
		newObject.vect[2] = vect[2] / n;
		newObject.vect[3] = vect[3] / n;
		return (newObject);
	}

	float Dot(Vector4 vecObj) //Dot product
	{
		return 	vect[0] * vecObj.vect[0] + vect[1] * vecObj.vect[1] + vect[2] * vecObj.vect[2];
	}

	static float StaticDot(Vector4 vec1, Vector4 vec2) //Dot product
	{
		return 	vec1.vect[0] * vec2.vect[0] + vec1.vect[1] * vec2.vect[1] + vec1.vect[2] * vec2.vect[2];
	}

	static float StaticDot4(Vector4 vec1, Vector4 vec2) //Dot product
	{
		return 	vec1.vect[0] * vec2.vect[0] + vec1.vect[1] * vec2.vect[1] + vec1.vect[2] * vec2.vect[2] + vec1.vect[3] * vec2.vect[3];
	}

	float Dot(Vector4 vec1, Vector4 vec2) //Dot product
	{
		return 	vec1.vect[0] * vec2.vect[0] + 
		vec1.vect[1] * vec2.vect[1] + 
		vec1.vect[2] * vec2.vect[2];
	}

	Vector4 VectScale(float n) //Scale vector ex. newVect = vector * 3.5f;
	{
		Vector4 newObject;
		newObject.vect[0] = vect[0] * n;
		newObject.vect[1] = vect[1] * n;
		newObject.vect[2] = vect[2] * n;
		newObject.vect[3] = vect[3] * n;
		return (newObject);
	}

	Vector4 operator*(Vector4 vecObj) //Cross product
	{
		Vector4 newObject;
		newObject.vect[0] = vect[1] * vecObj.vect[2] - vect[2] * vecObj.vect[1];
		newObject.vect[0] = -(vect[0] * vecObj.vect[2] - vect[2] * vecObj.vect[0]) ;
		newObject.vect[0] = vect[0] * vecObj.vect[1] - vect[1] * vecObj.vect[0];
		return (newObject);
	}

	bool operator==(Vector4 vecObj) //Compare if two vectors are equal
	{
		return (vect[0] == vecObj.vect[0] && vect[1] == vecObj.vect[1] && vect[2] == vecObj.vect[2] && vect[3] == vecObj.vect[3]);
	}

	float *VectorToArray()
	{
		return &vect[0];
	}
};

class MatrixLib4D
{


  public:
	float m[4][4];

	MatrixLib4D() //Identity matrix
	{

		//Row 1
		m[0][0] = 1;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;

		//Row 2
		m[1][0] = 0;
		m[1][1] = 1;
		m[1][2] = 0;
		m[1][3] = 0;

		//Row 3
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 1;
		m[2][3] = 0;

		//Row 4
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;
	}

	MatrixLib4D(
		float x0, float x1, float x2, float x3,
		float y0, float y1, float y2, float y3,
		float z0, float z1, float z2, float z3,
		float w0, float w1, float w2, float w3) //Constructor with applied values to the matrix.
	{
		//Row 1
		m[0][0] = x0;
		m[0][1] = x1;
		m[0][2] = x2;
		m[0][3] = x3;

		//Row 2
		m[1][0] = y0;
		m[1][1] = y1;
		m[1][2] = y2;
		m[1][3] = y3;

		//Row 3
		m[2][0] = z0;
		m[2][1] = z1;
		m[2][2] = z2;
		m[2][3] = z3;

		//Row 4
		m[3][0] = w0;
		m[3][1] = w1;
		m[3][2] = w2;
		m[3][3] = w3;
	}

	void Identity() //Constructor with applied values to the matrix.
	{
		
		m[0][0] = 1;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;

		m[1][0] = 0;
		m[1][1] = 1;
		m[1][2] = 0;
		m[1][3] = 0;
		
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 1;
		m[2][3] = 0;
		
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;
	}

	inline float* operator[](unsigned int i) {
        return &this->m[i][i];
    }

	Vector4 operator*(Vector4 vecObj) //Matrix * vector
	{
		Vector4 newObject;
		float newVectX = m[0][0] * vecObj.GetVectorValueByIndex(0) + m[0][1] * vecObj.GetVectorValueByIndex(1) + m[0][2] * vecObj.GetVectorValueByIndex(2) + m[0][3] * vecObj.GetVectorValueByIndex(3);
		float newVectY = m[1][0] * vecObj.GetVectorValueByIndex(0) + m[1][1] * vecObj.GetVectorValueByIndex(1) + m[1][2] * vecObj.GetVectorValueByIndex(2) + m[1][3] * vecObj.GetVectorValueByIndex(3);
		float newVectZ = m[2][0] * vecObj.GetVectorValueByIndex(0) + m[2][1] * vecObj.GetVectorValueByIndex(1) + m[2][2] * vecObj.GetVectorValueByIndex(2) + m[2][3] * vecObj.GetVectorValueByIndex(3);
		float newVectW = m[3][0] * vecObj.GetVectorValueByIndex(0) + m[3][1] * vecObj.GetVectorValueByIndex(1) + m[3][2] * vecObj.GetVectorValueByIndex(2) + m[3][3] * vecObj.GetVectorValueByIndex(3);
		newObject.SetVect(newVectX, newVectY, newVectZ, newVectW);
		return (newObject);
	}

	MatrixLib4D operator*(MatrixLib4D matrix) //Matrix * matrix
	{

		MatrixLib4D newObject;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				newObject.m[i][j] = m[i][0] * matrix.m[0][j] + m[i][1] * matrix.m[1][j] + m[i][2] * matrix.m[2][j] + m[i][3] * matrix.m[3][j];
			}
		}

		return (newObject);
	}

	MatrixLib4D operator*(float s) //Matrix * float -- to be able to scale each element
	{
		MatrixLib4D newObject;
		//Row 1
		newObject.m[0][0] = m[0][0] * s;
		newObject.m[0][1] = m[0][1] * s;
		newObject.m[0][2] = m[0][2] * s;
		newObject.m[0][3] = m[0][3] * s;

		//Row 2
		newObject.m[1][0] = m[1][0] * s;
		newObject.m[1][1] = m[1][1] * s;
		newObject.m[1][2] = m[1][2] * s;
		newObject.m[1][3] = m[1][3] * s;

		//Row 3
		newObject.m[2][0] = m[2][0] * s;
		newObject.m[2][1] = m[2][1] * s;
		newObject.m[2][2] = m[2][2] * s;
		newObject.m[2][3] = m[2][3] * s;

		//Row 4
		newObject.m[3][0] = m[3][0] * s;
		newObject.m[3][1] = m[3][1] * s;
		newObject.m[3][2] = m[3][2] * s;
		newObject.m[3][3] = m[3][3];

		return (newObject);
	}

	void ZeroMatrix()
	{
				//Row 1
		m[0][0] = 0;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;

		//Row 2
		m[1][0] = 0;
		m[1][1] = 0;
		m[1][2] = 0;
		m[1][3] = 0;

		//Row 3
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 0;
		m[2][3] = 0;

		//Row 4
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 0;
	}

	void ScaleByValue(float amount)
	{
		m[0][0] = 1 + amount;
		m[1][1] = 1 + amount;
		m[2][2] = 1 + amount;
	}

	void operator=(MatrixLib4D matrix) //Assignment matrix operator -- ex. matrix = matrix1;
	{

		//Row 1
		m[0][0] = matrix.m[0][0];
		m[0][1] = matrix.m[0][1];
		m[0][2] = matrix.m[0][2];
		m[0][3] = matrix.m[0][3];

		//Row 2
		m[1][0] = matrix.m[1][0];
		m[1][1] = matrix.m[1][1];
		m[1][2] = matrix.m[1][2];
		m[1][3] = matrix.m[1][3];

		//Row 3
		m[2][0] = matrix.m[2][0];
		m[2][1] = matrix.m[2][1];
		m[2][2] = matrix.m[2][2];
		m[2][3] = matrix.m[2][3];

		//Row 4
		m[3][0] = matrix.m[3][0];
		m[3][1] = matrix.m[3][1];
		m[3][2] = matrix.m[3][2];
		m[3][3] = matrix.m[3][3];
	}

	void SetMatrix(
		float x0, float x1, float x2, float x3,
		float y0, float y1, float y2, float y3,
		float z0, float z1, float z2, float z3,
		float w0, float w1, float w2, float w3) // Set values to matrix
	{
		//Row 1
		m[0][0] = x0;
		m[0][1] = x1;
		m[0][2] = x2;
		m[0][3] = x3;

		//Row 2
		m[1][0] = y0;
		m[1][1] = y1;
		m[1][2] = y2;
		m[1][3] = y3;

		//Row 3
		m[2][0] = z0;
		m[2][1] = z1;
		m[2][2] = z2;
		m[2][3] = z3;

		//Row 4
		m[3][0] = w0;
		m[3][1] = w1;
		m[3][2] = w2;
		m[3][3] = w3;
	}

	float GetMatrix4D(int x, int y)
	{
		return m[x][y];
	}

	void TransposeMatrix() //Transpose matrix
	{
		float temp[4][4];
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp[i][j] = m[i][j];
			}
		}

		//Row 1
		m[0][0] = temp[0][0];
		m[0][1] = temp[1][0];
		m[0][2] = temp[2][0];
		m[0][3] = temp[3][0];

		//Row 2
		m[1][0] = temp[0][1];
		m[1][1] = temp[1][1];
		m[1][2] = temp[2][1];
		m[1][3] = temp[3][1];

		//Row 3
		m[2][0] = temp[0][2];
		m[2][1] = temp[1][2];
		m[2][2] = temp[2][2];
		m[2][3] = temp[3][2];

		//Row 4
		m[3][0] = temp[0][3];
		m[3][1] = temp[1][3];
		m[3][2] = temp[2][3];
		m[3][3] = temp[3][3];
	}

	void SetPositionX(float x)
	{
		m[0][3] = x;
	}

	void SetPositionY(float y)
	{
		m[1][3] = y;
	}

	void SetPositionZ(float z)
	{
		m[2][3] = z;
	}

	MatrixLib4D QuatToMatrix(float qX, float qY, float qZ, float qW)
	{
		MatrixLib4D newObject;
		double sqw = qW * qW;
		double sqx = qX * qX;
		double sqy = qY * qY;
		double sqz = qZ * qZ;

		double invs = 1 / (sqx + sqy + sqz + sqw);

		newObject.m[0][0] = (sqx - sqy - sqz + sqw) * invs;
		newObject.m[1][1] = (-sqx + sqy - sqz + sqw) * invs;
		newObject.m[2][2] = (-sqx - sqy + sqz + sqw) * invs;

		double tmp1 = qX * qY;
		double tmp2 = qZ * qW;
		newObject.m[1][0] = 2.0 * (tmp1 + tmp2) * invs;
		newObject.m[0][1] = 2.0 * (tmp1 - tmp2) * invs;

		tmp1 = qX * qZ;
		tmp2 = qY * qW;
		newObject.m[2][0] = 2.0 * (tmp1 - tmp2) * invs;
		newObject.m[0][2] = 2.0 * (tmp1 + tmp2) * invs;
		tmp1 = qY * qZ;
		tmp2 = qX * qW;
		newObject.m[2][1] = 2.0 * (tmp1 + tmp2) * invs;
		newObject.m[1][2] = 2.0 * (tmp1 - tmp2) * invs;

		return (newObject);
	}

	MatrixLib4D Invert(MatrixLib4D out, MatrixLib4D in)
	{
		float 
		a00 = in.m[0][0], 
		a01 = in.m[0][1], 
		a02 = in.m[0][2], 
		a03 = in.m[0][3];
		float
		a10 = in.m[1][0], 
		a11 = in.m[1][1], 
		a12 = in.m[1][2], 
		a13 = in.m[1][3];
		float 
		a20 = in.m[2][0], 
		a21 = in.m[2][1], 
		a22 = in.m[2][2], 
		a23 = in.m[2][3];
		float 
		a30 = in.m[3][0], 
		a31 = in.m[3][1], 
		a32 = in.m[3][2], 
		a33 = in.m[3][3];

		float b00 = a00 * a11 - a01 * a10;
		float b01 = a00 * a12 - a02 * a10;
		float b02 = a00 * a13 - a03 * a10;
		float b03 = a01 * a12 - a02 * a11;
		float b04 = a01 * a13 - a03 * a11;
		float b05 = a02 * a13 - a03 * a12;
		float b06 = a20 * a31 - a21 * a30;
		float b07 = a20 * a32 - a22 * a30;
		float b08 = a20 * a33 - a23 * a30;
		float b09 = a21 * a32 - a22 * a31;
		float b10 = a21 * a33 - a23 * a31;
		float b11 = a22 * a33 - a23 * a32;
		// Calculate the determinant
		float det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
		if (!det) 
		{
			int hej = 3;
			// assert(true);
		}
		det = 1.0 / det;
		out.m[0][0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
		out.m[0][1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
		out.m[0][2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
		out.m[0][3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;

		out.m[1][0] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
		out.m[1][1] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
		out.m[1][2] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
		out.m[1][3] = (a20 * b05 - a22 * b02 + a23 * b01) * det;

		out.m[2][0] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
		out.m[2][1] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
		out.m[2][2] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
		out.m[2][3] = (a21 * b02 - a20 * b04 - a23 * b00) * det;

		out.m[3][0] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
		out.m[3][1] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
		out.m[3][2] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
		out.m[3][3] = (a20 * b03 - a21 * b01 + a22 * b00) * det;
		return out;
	}

	MatrixLib4D RotationX(float angle) //Rotation matrix around X-axis
	{
		float rad = angle * (pi / 180.0f);

		MatrixLib4D newObject;

		//Row 1
		newObject.m[0][0] = 1.0f;
		newObject.m[0][1] = 0.0f;
		newObject.m[0][2] = 0.0f;
		newObject.m[0][3] = 0.0f;

		//Row 2
		newObject.m[1][0] = 0.0f;
		newObject.m[1][1] = cos(rad);
		newObject.m[1][2] = -sin(rad);
		newObject.m[1][3] = 0.0f;

		//Row 3
		newObject.m[2][0] = 0.0f;
		newObject.m[2][1] = -sin(rad);
		newObject.m[2][2] = cos(rad);
		newObject.m[2][3] = 0.0f;

		//Row 4
		newObject.m[3][0] = 0.0f;
		newObject.m[3][1] = 0.0f;
		newObject.m[3][2] = 0.0f;
		newObject.m[3][3] = 1.0f;
		return (newObject);
	}

	MatrixLib4D RotationY(float angle) //Rotation matrix around Y-axis
	{
		float rad = angle * (pi / 180.0f);

		MatrixLib4D newObject;

		//Row 1
		newObject.m[0][0] = cos(rad);
		newObject.m[0][1] = 0.0f;
		newObject.m[0][2] = sin(rad);
		newObject.m[0][3] = 0.0f;

		//Row 2
		newObject.m[1][0] = 0.0f;
		newObject.m[1][1] = 1.0f;
		newObject.m[1][2] = 0.0f;
		newObject.m[1][3] = 0.0f;

		//Row 3
		newObject.m[2][0] = -sin(rad);
		newObject.m[2][1] = 0.0f;
		newObject.m[2][2] = cos(rad);
		newObject.m[2][3] = 0.0f;

		//Row 4
		newObject.m[3][0] = 0.0f;
		newObject.m[3][1] = 0.0f;
		newObject.m[3][2] = 0.0f;
		newObject.m[3][3] = 1.0f;
		return (newObject);
	}

	MatrixLib4D RotationZ(float angle) //Rotation matrix around Z-axis
	{
		float rad = angle * (pi / 180.0f);

		MatrixLib4D newObject;

		//Row 1
		newObject.m[0][0] = cos(rad);
		newObject.m[0][1] = -sin(rad);
		newObject.m[0][2] = 0.0f;
		newObject.m[0][3] = 0.0f;

		//Row 2
		newObject.m[1][0] = sin(rad);
		newObject.m[1][1] = cos(rad);
		newObject.m[1][2] = 0.0f;
		newObject.m[1][3] = 0.0f;

		//Row 3
		newObject.m[2][0] = 0.0f;
		newObject.m[2][1] = 0.0f;
		newObject.m[2][2] = 1.0f;
		newObject.m[2][3] = 0.0f;

		//Row 4
		newObject.m[3][0] = 0.0f;
		newObject.m[3][1] = 0.0f;
		newObject.m[3][2] = 0.0f;
		newObject.m[3][3] = 1.0f;
		return (newObject);
	}

	void RotateX(float angle) //Rotation matrix around X-axis
	{
		float rad = angle * (pi / 180.0f);
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = cos(rad);
		m[1][2] = -sin(rad);
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = -sin(rad);
		m[2][2] = cos(rad);
		m[2][3] = 0.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void RotateY(float angle) //Rotation matrix around Y-axis
	{
		float rad = angle * (pi / 180.0f);
		m[0][0] = cos(rad);
		m[0][1] = 0.0f;
		m[0][2] = sin(rad);
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = -sin(rad);
		m[2][1] = 0.0f;
		m[2][2] = cos(rad);
		m[2][3] = 0.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void RotateZ(float angle) //Rotation matrix around Z-axis
	{
		float rad = angle * (pi / 180.0f);
		m[0][0] = cos(rad);
		m[0][1] = -sin(rad);
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = sin(rad);
		m[1][1] = cos(rad);
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
		m[2][3] = 0.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void SetUpRotationMatrix(float angle, float u, float v, float w) //Rotation around arbitrary axis (u, v, w)
	{

		float L = (u * u + v * v + w * w);
		float rad = angle * (pi / 180.0f);
		float u2 = u * u;
		float v2 = v * v;
		float w2 = w * w;

		m[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
		m[0][1] = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
		m[0][2] = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;
		m[0][3] = 0.0;

		m[1][0] = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
		m[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
		m[1][2] = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;
		m[1][3] = 0.0;

		m[2][0] = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
		m[2][1] = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
		m[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;
		m[2][3] = 0.0;

		m[3][0] = 0.0;
		m[3][1] = 0.0;
		m[3][2] = 0.0;
		m[3][3] = 1.0;
	}

	MatrixLib4D TranslateAndRotateZ(float angle, float x, float y, float z)
	{
		float rad = angle * (pi / 180.0f);
		return MatrixLib4D(
			cos(rad), -sin(rad), .0f, x,
			sin(rad), cos(rad), .0f, y,
			.0f, .0f, 1.0f, z,
			.0f, .0f, .0f, 1.0f);
	}

	void TranslateX(float x)
	{
		m[0][3] = x;
	}

	void TranslateY(float y)
	{
		m[1][3] = y;
	}

	void TranslateZ(float z)
	{
		m[2][3] = z;
	}

	void Translate(Vector3 vec)
	{
		m[0][3] = vec.x;
		m[1][3] = vec.y;
		m[2][3] = vec.z;
	}

	Vector3 GetTranslation()
	{
		return Vector3
		(
			m[0][3],
			m[1][3],
			m[2][3]
		);
	}

	float *MatrixToArray()
	{
		return &m[0][0];
	}

	void CopyRotationY(MatrixLib4D rotatedMatrix)
	{
		m[0][0] = rotatedMatrix.m[0][0];
		m[0][2] = rotatedMatrix.m[0][2];

		m[2][0] = rotatedMatrix.m[2][0];
		m[2][2] = rotatedMatrix.m[2][2];
	}



	void SetMatrixByIndex(int column, int row, float value)
	{
		m[column][row] = value; //dont trust this
	}


	// MatrixLib4D Perspective(float angle, float ratio, float near, float far)
	// {
	// 	MatrixLib4D tempMatrix;
	// 	tempMatrix.ZeroMatrix();
	// 	float tan_half_angle;

	// 	tan_half_angle = tan(angle / 2);
	// 	tempMatrix.SetMatrixByIndex(0, 0, 1 / (ratio * tan_half_angle));
	// 	tempMatrix.SetMatrixByIndex(1, 1, 1 / (tan_half_angle));
	// 	tempMatrix.SetMatrixByIndex(2, 2, -(far + near) / (far - near));

	// 	//Transposed
	// 	tempMatrix.SetMatrixByIndex(3, 2, -1);
	// 	tempMatrix.SetMatrixByIndex(2, 3, -(2 * far * near) / (far - near));

	// 	//Not transposed
	// 	// tempMatrix.SetMatrixByIndex(2, 3, -1);
	// 	// tempMatrix.SetMatrixByIndex(3, 2, -(2 * far * near) / (far - near));
	// 	return (tempMatrix);
	// }

	MatrixLib4D Perspective(float angleInDegrees, float ratio, float near, float far)
	{
		MatrixLib4D tempMatrix;
		tempMatrix.ZeroMatrix();
		float tan_half_angle;
		float angleInRadians = angleInDegrees * (pi / 180.0f);

		tan_half_angle = tan(angleInRadians / 2);
		tempMatrix.SetMatrixByIndex(0, 0, 1 / (ratio * tan_half_angle));
		tempMatrix.SetMatrixByIndex(1, 1, 1 / (tan_half_angle));
		tempMatrix.SetMatrixByIndex(2, 2, -(far + near) / (far - near));

		//Transposed
		//  tempMatrix.SetMatrixByIndex(2, 3, -1);
		//  tempMatrix.SetMatrixByIndex(3, 2, -(2 * far * near) / (far - near));

		//Not transposed
		tempMatrix.SetMatrixByIndex(3, 2, -1);
		tempMatrix.SetMatrixByIndex(2, 3, -(2 * far * near) / (far - near));
		return (tempMatrix);

		// template<typename T>
		// GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveRH_NO(T fovy, T aspect, T zNear, T zFar)
		// {
		// 	assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

		// 	T const tanHalfFovy = tan(fovy / static_cast<T>(2));

		// 	mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		// 	Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
		// 	Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
		// 	Result[2][2] = - (zFar + zNear) / (zFar - zNear);
		// 	Result[2][3] = - static_cast<T>(1);
		// 	Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
		// 	return Result;
		// }

	}



	static MatrixLib4D LookAt(MatrixLib4D& view, Vector3 eye, Vector3 center, Vector3 up) 
	{
		float x0, x1, x2, y0, y1, y2, z0, z1, z2, len;
		float eyex = eye.x;
		float eyey = eye.y;
		float eyez = eye.z;
		float upx = up.x;
		float upy = up.y;
		float upz = up.z;
		float centerx = center.x;
		float centery = center.y;
		float centerz = center.z;

		if (abs(eyex - centerx) < 0.00001f &&
			abs(eyey - centery) < 0.00001f &&
			abs(eyez - centerz) < 0.00001f) 
		{
			return MatrixLib4D();
		}

		z0 = eyex - centerx;
		z1 = eyey - centery;
		z2 = eyez - centerz;
		len = 1 / sqrt(z0 * z0 + z1 * z1 + z2 * z2);

		z0 *= len;
		z1 *= len;
		z2 *= len;

		x0 = upy * z2 - upz * z1;
		x1 = upz * z0 - upx * z2;
		x2 = upx * z1 - upy * z0;

		len = sqrt(x0 * x0 + x1 * x1 + x2 * x2);
		if (!len) 
		{
			x0 = 0;
			x1 = 0;
			x2 = 0;
		} 
		else 
		{
			len = 1 / len;
			x0 *= len;
			x1 *= len;
			x2 *= len;
		}
		y0 = z1 * x2 - z2 * x1;
		y1 = z2 * x0 - z0 * x2;
		y2 = z0 * x1 - z1 * x0;
		len = sqrt(y0 * y0 + y1 * y1 + y2 * y2);
		if (!len) 
		{
			y0 = 0;
			y1 = 0;
			y2 = 0;
		}
		else 
		{
			len = 1 / len;
			y0 *= len;
			y1 *= len;
			y2 *= len;
		}

		view.m[0][0] = x0;
		view.m[0][1] = y0;
		view.m[0][2] = z0;
		view.m[0][3] = 0;

		view.m[1][0] = x1;
		view.m[1][1] = y1;
		view.m[1][2] = z1;
		view.m[1][3] = 0;

		view.m[2][0] = x2;
		view.m[2][1] = y2;
		view.m[2][2] = z2;
		view.m[2][3] = 0;

		view.m[3][0] = -(x0 * eyex + x1 * eyey + x2 * eyez);
		view.m[3][1] = -(y0 * eyex + y1 * eyey + y2 * eyez);
		view.m[3][2] = -(z0 * eyex + z1 * eyey + z2 * eyez);
		view.m[3][3] = 1.0f;
		view.TransposeMatrix();
		return view;
	}
};