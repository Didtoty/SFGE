/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <p2vector.h>
#include <cmath>

// -----------------------------------------
// ----------- CLASS : p2Vec2 --------------
// -----------------------------------------
p2Vec2::p2Vec2()
{
}

p2Vec2::p2Vec2(float x, float y) : x(x), y(y)
{
}

p2Vec2 p2Vec2::operator+(p2Vec2 v)
{
	return p2Vec2(this->x + v.x, this->y + v.y);
}

p2Vec2 p2Vec2::operator+=(p2Vec2 v)
{
	this->x += v.x;
	this->y += v.y;
	return p2Vec2(this->x, this->y);
}

p2Vec2 p2Vec2::operator-(p2Vec2 v)
{
	return p2Vec2(this->x - v.x, this->y - v.y);
}

p2Vec2 p2Vec2::operator-=(p2Vec2 v)
{
	this->x -= v.x;
	this->y -= v.y;
	return p2Vec2(this->x, this->y);
}

p2Vec2 p2Vec2::operator/(float f)
{
	return p2Vec2(this->x / f, this->y / f);
}

p2Vec2 p2Vec2::operator*(float f)
{
	return p2Vec2(this->x * f, this->y * f);
}

bool p2Vec2::operator==(p2Vec2 v)
{
	return (this->x == v.x && this->y == v.y);
}

float p2Vec2::Dot(p2Vec2 v1, p2Vec2 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

p2Vec3 p2Vec2::Cross(p2Vec2 v1, p2Vec2 v2)
{
	return p2Vec3::Cross(v1.to3(), v2.to3());
}

p2Vec2 p2Vec2::Lerp(p2Vec2 v1, p2Vec2 v2, float t)
{
	return v1 + ((v2-v1) * t);
}

p2Vec2 p2Vec2::Proj(p2Vec2 v1, p2Vec2 v2)
{
	return v2 * (Dot(v1, v2) / v2.GetMagnitude());
}

p2Vec2 p2Vec2::Refl(p2Vec2 v1, p2Vec2 n)
{
	return v1 - n.Normalized() * 2 * Dot(v1, n.Normalized());
}

float p2Vec2::AngleBetween(p2Vec2 v1, p2Vec2 v2)
{
	return acos(Dot(v1, v2) / v1.GetMagnitude() / v2.GetMagnitude());
}

float p2Vec2::GetMagnitude()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

p2Vec2 p2Vec2::Normalized()
{
	return p2Vec2(this->x, this->y) / this->GetMagnitude();
}

void p2Vec2::Normalize()
{
	float magnitude = this->GetMagnitude();
	this->x /= magnitude;
	this->y /= magnitude;
}

p2Vec3 p2Vec2::to3()
{
	return p2Vec3(this->x, this->y, 0.0f);
}

// -----------------------------------------
// ----------- CLASS : p2Vec3 --------------
// -----------------------------------------
p2Vec3::p2Vec3()
{
}

p2Vec3::p2Vec3(float x, float y, float z) : x(x), y(y), z(z)
{
}

p2Vec3 p2Vec3::operator+(p2Vec3 v)
{
	return p2Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
}

p2Vec3 p2Vec3::operator+=(p2Vec3 v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return p2Vec3(this->x, this->y, this->z);
}

p2Vec3 p2Vec3::operator-(p2Vec3 v)
{
	return p2Vec3(this->x - v.x, this->y - v.y, this->z - v.z);
}

p2Vec3 p2Vec3::operator-=(p2Vec3 v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return p2Vec3(this->x, this->y, this->z);
}

p2Vec3 p2Vec3::operator/(float f)
{
	return p2Vec3(this->x / f, this->y / f, this->z / f);
}

p2Vec3 p2Vec3::operator*(float f)
{
	return p2Vec3(this->x * f, this->y * f, this->z * f);
}

bool p2Vec3::operator==(p2Vec3 v)
{
	return (this->x == v.x && this->y == v.y && this->z == v.z);
}

float p2Vec3::Dot(p2Vec3 v1, p2Vec3 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

p2Vec3 p2Vec3::Cross(p2Vec3 v1, p2Vec3 v2)
{
	return p2Vec3(v1.y * v2.z - v1.z * v2.y, 
			v1.x * v2.z - v1.z * v2.x, 
			v1.x * v2.y - v1.y * v2.x);
}

p2Vec3 p2Vec3::Lerp(p2Vec3 v1, p2Vec3 v2, float t)
{
	return v1 + ((v2 - v1) * t);
}

p2Vec3 p2Vec3::Proj(p2Vec3 v1, p2Vec3 v2)
{
	return v2 * (Dot(v1, v2) / v2.GetMagnitude());
}

p2Vec3 p2Vec3::Refl(p2Vec3 v1, p2Vec3 n)
{
	return v1 - n.Normalized() * 2 * Dot(v1, n.Normalized());
}

float p2Vec3::AngleBetween(p2Vec3 v1, p2Vec3 v2)
{
	return acos(Dot(v1, v2) / v1.GetMagnitude() / v2.GetMagnitude());
}

float p2Vec3::GetMagnitude()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

p2Vec3 p2Vec3::Normalized()
{
	return p2Vec3(this->x, this->y, this->z) / this->GetMagnitude();
}

void p2Vec3::Normalize()
{
	float magnitude = this->GetMagnitude();
	this->x /= magnitude;
	this->y /= magnitude;
	this->z /= magnitude;
}