#pragma once
#include "GameManager.h"


class Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float _x, float _y, float _z);
	~Vector3();
	void Print();
	static Vector3 Random(float a, float b)
	{
		float _x = rand() % ((int)(round(b - a)) + 1) + a;
		float _y = rand() % ((int)(round(b - a)) + 1) + a;
		float _z = rand() % ((int)(round(b - a)) + 1) + a;
		return { _x, _y, _z };
	}

	static Vector3 Lerp(Vector3 a, Vector3 b, float t)
	{
		if (t >= 1)
		{
			t = 1;
		}
		Vector3 resVector = b - a;
		/*resVector.x = LerpFloat(a.x, b.x, t);
		resVector.y = LerpFloat(a.y, b.y, t);
		resVector.z = LerpFloat(a.z, b.z, t);*/

		resVector = resVector * t + a;
		return resVector;
	}

	Vector3 operator+(Vector3 secondVector)
	{
		Vector3 temp(this->x + secondVector.x, this->y + secondVector.y, this->z + secondVector.z);
		return temp;
	}
	
	Vector3 operator-(Vector3 secondVector)
	{
		Vector3 temp(this->x - secondVector.x, this->y - secondVector.y, this->z - secondVector.z);
		return temp;
	}
	
	Vector3 operator*(float num)
	{
		Vector3 temp(this->x * num, this->y * num, this->z * num);
		return temp;
	}

private:

};

