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

#include <p2matrix.h>

p2Mat22::p2Mat22()
{
}

p2Mat22::p2Mat22(p2Vec2 c1, p2Vec2 c2)
{
	this->columns[0] = c1;
	this->columns[1] = c2;
}

p2Mat22 p2Mat22::operator+(p2Mat22 m1)
{
	return p2Mat22(this->columns[0] + m1.columns[0], this->columns[1] + m1.columns[1]);
}

p2Mat22 p2Mat22::operator+=(p2Mat22 m1)
{
	return *this = *this + m1;
}

p2Mat22 p2Mat22::operator-(p2Mat22 m1)
{
	return p2Mat22(this->columns[0] - m1.columns[0], this->columns[1] - m1.columns[1]);
}

p2Mat22 p2Mat22::operator-=(p2Mat22 m1)
{
	return *this = *this - m1;
}

p2Mat22 p2Mat22::operator*(p2Mat22 m1)
{
	return p2Mat22(
		p2Vec2(this->columns[0].x * m1.columns[0].x + this->columns[1].x * m1.columns[0].y, 
			   this->columns[0].x * m1.columns[1].x + this->columns[1].x * m1.columns[1].y
			),
		p2Vec2(this->columns[0].y * m1.columns[0].x + this->columns[1].y * m1.columns[0].y,
			   this->columns[0].y * m1.columns[1].x + this->columns[1].y * m1.columns[1].y
			)
	);
}

p2Mat22 p2Mat22::operator*=(p2Mat22 m1)
{
	return *this = *this * m1;
}

p2Vec2 p2Mat22::operator*(p2Vec2 v)
{
	return p2Vec2(
		this->columns[0].x * v.x + this->columns[1].x * v.y,
		this->columns[0].y * v.x + this->columns[1].y * v.y
	);
}

p2Mat22 p2Mat22::operator*(float f)
{
	return p2Mat22(
		p2Vec2(this->columns[0].x * f, this->columns[0].y * f),
		p2Vec2(this->columns[1].x * f, this->columns[1].y * f)
	);
}

p2Mat22 p2Mat22::operator*=(float f)
{
	return *this = *this * f;
}

p2Mat22 p2Mat22::operator/(float f)
{
	return p2Mat22(
		p2Vec2(this->columns[0].x / f, this->columns[0].y / f),
		p2Vec2(this->columns[1].x / f, this->columns[1].y / f)
	);
}

p2Mat22 p2Mat22::operator/=(float f)
{
	return *this = *this / f;
}

bool p2Mat22::operator==(p2Mat22 m1)
{
	return this->columns[0].x == m1.columns[0].x &&
		this->columns[0].y == m1.columns[0].y &&
		this->columns[1].x == m1.columns[1].x &&
		this->columns[1].y == m1.columns[1].y;
}

p2Mat22 p2Mat22::Invert()
{
	float det = this->GetDeterminant();
	if(det == 0)
		return p2Mat22(this->columns[0], this->columns[1]);
	else
	{
		return p2Mat22(
			p2Vec2(this->columns[1].y, -this->columns[0].y),
			p2Vec2(-this->columns[1].x, this->columns[0].x)
		) / det;
	}

}

float p2Mat22::GetDeterminant()
{
	return this->columns[0].x  * this->columns[1].y - this->columns[1].x  * this->columns[0].y;
}

void p2Mat22::printDebug()
{
	std::cout << "| " << columns[0].x << " | " << columns[1].x << " |\n";
	std::cout << "| " << columns[0].y << " | " << columns[1].y << " |\n";
}

p2Mat33::p2Mat33()
{
}

p2Mat33::p2Mat33(p2Vec3 c1, p2Vec3 c2, p2Vec3 c3)
{
	this->columns[0] = c1;
	this->columns[1] = c2;
	this->columns[2] = c3;
}

p2Mat33 p2Mat33::operator+(p2Mat33 m1)
{
	return p2Mat33(this->columns[0] + m1.columns[0], this->columns[1] + m1.columns[1], this->columns[2] + m1.columns[2]);
}

p2Mat33 p2Mat33::operator+=(p2Mat33 m1)
{
	return *this = *this + m1;
}

p2Mat33 p2Mat33::operator-(p2Mat33 m1)
{
	return p2Mat33(this->columns[0] - m1.columns[0], this->columns[1] - m1.columns[1], this->columns[2] - m1.columns[2]);
}

p2Mat33 p2Mat33::operator-=(p2Mat33 m1)
{
	return *this = *this - m1;
}

p2Mat33 p2Mat33::operator*(p2Mat33 m1)
{
	return p2Mat33(
		p2Vec3(
			this->columns[0].x * m1.columns[0].x + this->columns[1].x * m1.columns[0].y + this->columns[2].x * m1.columns[0].z,
			this->columns[0].y * m1.columns[0].x + this->columns[1].y * m1.columns[0].y + this->columns[2].y * m1.columns[0].z,
			this->columns[0].z * m1.columns[0].x + this->columns[1].z * m1.columns[0].y + this->columns[2].z * m1.columns[0].z
		), 
		p2Vec3(
			this->columns[0].x * m1.columns[1].x + this->columns[1].x * m1.columns[1].y + this->columns[2].x * m1.columns[1].z,
			this->columns[0].y * m1.columns[1].x + this->columns[1].y * m1.columns[1].y + this->columns[2].y * m1.columns[1].z,
			this->columns[0].z * m1.columns[1].x + this->columns[1].z * m1.columns[1].y + this->columns[2].z * m1.columns[1].z
		), 
		p2Vec3(
			this->columns[0].x * m1.columns[2].x + this->columns[1].x * m1.columns[2].y + this->columns[2].x * m1.columns[2].z,
			this->columns[0].y * m1.columns[2].x + this->columns[1].y * m1.columns[2].y + this->columns[2].y * m1.columns[2].z,
			this->columns[0].z * m1.columns[2].x + this->columns[1].z * m1.columns[2].y + this->columns[2].z * m1.columns[2].z
		)
	);
}

p2Mat33 p2Mat33::operator*=(p2Mat33 m1)
{
	return *this = *this * m1;
}

p2Vec3 p2Mat33::operator*(p2Vec3 v)
{
	return p2Vec3(
		this->columns[0].x * v.x + this->columns[1].x * v.y + this->columns[2].x * v.z,
		this->columns[0].y * v.x + this->columns[1].y * v.y + this->columns[2].y * v.z,
		this->columns[0].z * v.x + this->columns[1].z * v.y + this->columns[2].z * v.z
	);
}

p2Mat33 p2Mat33::operator*(float f)
{
	return p2Mat33(
		this->columns[0] * f,
		this->columns[1] * f,
		this->columns[2] * f
	);
}

p2Mat33 p2Mat33::operator*=(float f)
{
	return *this = *this * f;
}

p2Mat33 p2Mat33::operator/(float f)
{
	return p2Mat33(
		p2Vec3(this->columns[0].x / f, this->columns[0].y / f, this->columns[0].z / f),
		p2Vec3(this->columns[1].x / f, this->columns[1].y / f, this->columns[1].z / f),
		p2Vec3(this->columns[2].x / f, this->columns[2].y / f, this->columns[2].z / f)
	);
}

p2Mat33 p2Mat33::operator/=(float f)
{
	return *this = *this / f;
}

bool p2Mat33::operator==(p2Mat33 m1)
{
	return this->columns[0].x == m1.columns[0].x &&
		this->columns[0].y == m1.columns[0].y &&
		this->columns[0].z == m1.columns[0].z &&
		this->columns[1].x == m1.columns[1].x &&
		this->columns[1].y == m1.columns[1].y &&
		this->columns[1].z == m1.columns[1].z &&
		this->columns[2].x == m1.columns[2].x &&
		this->columns[2].y == m1.columns[2].y &&
		this->columns[2].z == m1.columns[2].z;
}

p2Mat33 p2Mat33::Invert()
{
	float det = this->GetDeterminant();
	if(det == 0)
		return p2Mat33(this->columns[0], this->columns[1], this->columns[2]);
	else
	{
		p2Mat33 res = this->Transpose();
		// Calculate the adjacent
		res = p2Mat33
		(
			p2Vec3(
				res.columns[1].y * res.columns[2].z - res.columns[2].y * res.columns[1].z, 
				res.columns[1].x * res.columns[2].z - res.columns[2].x * res.columns[1].z, 
				res.columns[1].x * res.columns[2].y - res.columns[2].x * res.columns[1].y
			),
			p2Vec3(
				res.columns[0].y * res.columns[2].z - res.columns[2].y * res.columns[0].z, 
				res.columns[0].x * res.columns[2].z - res.columns[2].x * res.columns[0].z, 
				res.columns[0].x * res.columns[2].y - res.columns[2].x * res.columns[0].y
			),
			p2Vec3(
				res.columns[0].y * res.columns[1].z - res.columns[1].y * res.columns[0].z, 
				res.columns[0].x * res.columns[1].z - res.columns[1].x * res.columns[0].z, 
				res.columns[0].x * res.columns[1].y - res.columns[1].x * res.columns[0].y
			)
		);

		//Apply negativity
		res.columns[1].x = -res.columns[1].x;
		res.columns[0].y = -res.columns[0].y;
		res.columns[2].y = -res.columns[2].y;
		res.columns[1].z = -res.columns[1].z;

		return res / det;
	}
}

p2Mat33 p2Mat33::Transpose()
{
	return p2Mat33(
		p2Vec3(this->columns[0].x, this->columns[1].x, this->columns[2].x),
		p2Vec3(this->columns[0].y, this->columns[1].y, this->columns[2].y),
		p2Vec3(this->columns[0].z, this->columns[1].z, this->columns[2].z)
	);
}

float p2Mat33::GetDeterminant()
{
	return this->columns[0].x * (this->columns[1].y  * this->columns[2].z - this->columns[1].z  * this->columns[2].y) -
		this->columns[1].x * (this->columns[0].y  * this->columns[2].z - this->columns[0].z  * this->columns[2].y) +
		this->columns[2].x * (this->columns[0].y  * this->columns[1].z - this->columns[0].z  * this->columns[1].y);
}

void p2Mat33::printDebug()
{
	std::cout << "| " << columns[0].x << " | " << columns[1].x << " | " << columns[2].x << " |\n";
	std::cout << "| " << columns[0].y << " | " << columns[1].y << " | " << columns[2].y << " |\n";
	std::cout << "| " << columns[0].z << " | " << columns[1].z << " | " << columns[2].z << " |\n";
}
