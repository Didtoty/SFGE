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

p2Mat22::p2Mat22(p2Vec2 r1, p2Vec2 r2)
{
	this->rows[0] = r1;
	this->rows[1] = r2;
}

p2Mat22 p2Mat22::operator+(p2Mat22 m1)
{
	return p2Mat22(this->rows[0] + m1.rows[0], this->rows[1] + m1.rows[1]);
}

p2Mat22 p2Mat22::operator+=(p2Mat22 m1)
{
	this->rows[0] + m1.rows[0]; 
	this->rows[1] + m1.rows[1];
	return p2Mat22(this->rows[0], this->rows[1]);
}

p2Mat22 p2Mat22::operator-(p2Mat22 m1)
{
	return p2Mat22(this->rows[0] - m1.rows[0], this->rows[1] - m1.rows[1]);
}

p2Mat22 p2Mat22::operator-=(p2Mat22 m1)
{
	this->rows[0] - m1.rows[0];
	this->rows[1] - m1.rows[1];
	return p2Mat22(this->rows[0], this->rows[1]);
}

p2Mat22 p2Mat22::operator*(p2Mat22 m1)
{
	return p2Mat22(
		p2Vec2(this->rows[0].x * m1.rows[0].x + this->rows[1].x * m1.rows[0].y, 
			   this->rows[0].x * m1.rows[1].x + this->rows[1].x * m1.rows[1].y
			),
		p2Vec2(this->rows[0].y * m1.rows[0].x + this->rows[1].y * m1.rows[0].y,
			   this->rows[0].y * m1.rows[1].x + this->rows[1].y * m1.rows[1].y
			)
	);
}

p2Mat22 p2Mat22::operator*=(p2Mat22 m1)
{
	this->rows[0].x = this->rows[0].x * m1.rows[0].x + this->rows[1].x * m1.rows[0].y;
	this->rows[0].y = this->rows[0].x * m1.rows[1].x + this->rows[1].x * m1.rows[1].y;
	this->rows[0].x = this->rows[0].y * m1.rows[0].x + this->rows[1].y * m1.rows[0].y;
	this->rows[1].y = this->rows[0].y * m1.rows[1].x + this->rows[1].y * m1.rows[1].y;

	return p2Mat22(this->rows[0], this->rows[1]);
}

p2Vec2 p2Mat22::operator*(p2Vec2 v)
{
	return p2Vec2(
		this->rows[0].x * v.x + this->rows[1].x * v.y,
		this->rows[0].y * v.x + this->rows[1].y * v.y
	);
}

p2Mat22 p2Mat22::operator*(float f)
{
	return p2Mat22(
		p2Vec2(this->rows[0].x * f, this->rows[0].y * f),
		p2Vec2(this->rows[1].x * f, this->rows[1].y * f)
	);
}

p2Mat22 p2Mat22::operator*=(float f)
{
	this->rows[0] = p2Vec2(this->rows[0].x * f, this->rows[0].y * f);
	this->rows[1] = p2Vec2(this->rows[1].x * f, this->rows[1].y * f);
	return p2Mat22(this->rows[0], this->rows[1]);
}

p2Mat22 p2Mat22::operator/(float f)
{
	return p2Mat22(
		p2Vec2(this->rows[0].x / f, this->rows[0].y / f),
		p2Vec2(this->rows[1].x / f, this->rows[1].y / f)
	);
}

p2Mat22 p2Mat22::operator/=(float f)
{
	this->rows[0] = p2Vec2(this->rows[0].x / f, this->rows[0].y / f);
	this->rows[1] = p2Vec2(this->rows[1].x / f, this->rows[1].y / f);
	return p2Mat22(this->rows[0], this->rows[1]);
}

p2Mat22 p2Mat22::Invert()
{
	float det = this->GetDeterminant();
	if(det == 0)
		return p2Mat22(this->rows[0], this->rows[1]);
	else
	{
		return p2Mat22(
			p2Vec2(this->rows[1].y, -this->rows[0].y),
			p2Vec2(-this->rows[1].x, this->rows[0].x)
		) / det;
	}

}

float p2Mat22::GetDeterminant()
{
	return this->rows[0].x  * this->rows[1].y - this->rows[1].x  * this->rows[0].y;
}

p2Mat33::p2Mat33()
{
}

p2Mat33::p2Mat33(p2Vec3 r1, p2Vec3 r2, p2Vec3 r3)
{
	this->rows[0] = r1;
	this->rows[1] = r2;
	this->rows[2] = r3;
}

p2Mat33 p2Mat33::operator+(p2Mat33 m1)
{
	return p2Mat33(this->rows[0] + m1.rows[0], this->rows[1] + m1.rows[1], this->rows[2] + m1.rows[2]);
}

p2Mat33 p2Mat33::operator+=(p2Mat33 m1)
{
	this->rows[0] + m1.rows[0];
	this->rows[1] + m1.rows[1];
	this->rows[2] + m1.rows[2];
	return p2Mat33(this->rows[0], this->rows[1], this->rows[2]);
}

p2Mat33 p2Mat33::operator-(p2Mat33 m1)
{
	return p2Mat33(this->rows[0] - m1.rows[0], this->rows[1] - m1.rows[1], this->rows[2] - m1.rows[2]);
}

p2Mat33 p2Mat33::operator-=(p2Mat33 m1)
{
	this->rows[0] - m1.rows[0];
	this->rows[1] - m1.rows[1];
	this->rows[2] - m1.rows[2];
	return p2Mat33(this->rows[0], this->rows[1], this->rows[2]);
}

p2Mat33 p2Mat33::operator*(p2Mat33 m1)
{
	return p2Mat33(
		p2Vec3(
			this->rows[0].x * m1.rows[0].x + this->rows[0].y * m1.rows[1].x + this->rows[0].z * m1.rows[2].x,
			this->rows[0].x * m1.rows[0].y + this->rows[0].y * m1.rows[1].y + this->rows[0].z * m1.rows[2].y,
			this->rows[0].x * m1.rows[0].z + this->rows[0].y * m1.rows[1].z + this->rows[0].z * m1.rows[2].z
		), 
		p2Vec3(
			this->rows[1].x * m1.rows[0].x + this->rows[1].y * m1.rows[1].x + this->rows[1].z * m1.rows[2].x,
			this->rows[1].x * m1.rows[0].y + this->rows[1].y * m1.rows[1].y + this->rows[1].z * m1.rows[2].y,
			this->rows[1].x * m1.rows[0].z + this->rows[1].y * m1.rows[1].z + this->rows[1].z * m1.rows[2].z
		), 
		p2Vec3(
			this->rows[2].x * m1.rows[0].x + this->rows[2].y * m1.rows[1].x + this->rows[2].z * m1.rows[2].x,
			this->rows[2].x * m1.rows[0].y + this->rows[2].y * m1.rows[1].y + this->rows[2].z * m1.rows[2].y,
			this->rows[2].x * m1.rows[0].z + this->rows[2].y * m1.rows[1].z + this->rows[2].z * m1.rows[2].z
		)
	);
}

p2Mat33 p2Mat33::operator*=(p2Mat33 m1)
{
	this->rows[0].x = this->rows[0].x * m1.rows[0].x + this->rows[0].y * m1.rows[1].x + this->rows[0].z * m1.rows[2].x;
	this->rows[0].y = this->rows[0].x * m1.rows[0].y + this->rows[0].y * m1.rows[1].y + this->rows[0].z * m1.rows[2].y;
	this->rows[0].z = this->rows[0].x * m1.rows[0].z + this->rows[0].y * m1.rows[1].z + this->rows[0].z * m1.rows[2].z;

	this->rows[1].x = this->rows[1].x * m1.rows[0].x + this->rows[1].y * m1.rows[1].x + this->rows[1].z * m1.rows[2].x;
	this->rows[1].y = this->rows[1].x * m1.rows[0].y + this->rows[1].y * m1.rows[1].y + this->rows[1].z * m1.rows[2].y;
	this->rows[1].z = this->rows[1].x * m1.rows[0].z + this->rows[1].y * m1.rows[1].z + this->rows[1].z * m1.rows[2].z;

	this->rows[2].x = this->rows[2].x * m1.rows[0].x + this->rows[2].y * m1.rows[1].x + this->rows[2].z * m1.rows[2].x;
	this->rows[2].y = this->rows[2].x * m1.rows[0].y + this->rows[2].y * m1.rows[1].y + this->rows[2].z * m1.rows[2].y;
	this->rows[2].z = this->rows[2].x * m1.rows[0].z + this->rows[2].y * m1.rows[1].z + this->rows[2].z * m1.rows[2].z;
	
	return p2Mat33(this->rows[0], this->rows[1], this->rows[2]);
}

p2Vec3 p2Mat33::operator*(p2Vec3 v)
{
	return p2Vec3(
		this->rows[0].x * v.x + this->rows[0].y * v.x + this->rows[0].z * v.x,
		this->rows[0].x * v.y + this->rows[0].y * v.y + this->rows[0].z * v.y,
		this->rows[0].x * v.z + this->rows[0].y * v.z + this->rows[0].z * v.z
	);
}

p2Mat33 p2Mat33::operator*(float f)
{
	return p2Mat33(
		p2Vec3(this->rows[0].x * f, this->rows[0].y * f, this->rows[0].z * f),
		p2Vec3(this->rows[1].x * f, this->rows[1].y * f, this->rows[1].z * f),
		p2Vec3(this->rows[2].x * f, this->rows[2].y * f, this->rows[2].z * f)
	);
}

p2Mat33 p2Mat33::operator*=(float f)
{
	this->rows[0] = p2Vec3(this->rows[0].x * f, this->rows[0].y * f, this->rows[0].z * f);
	this->rows[1] = p2Vec3(this->rows[1].x * f, this->rows[1].y * f, this->rows[1].z * f);
	this->rows[2] = p2Vec3(this->rows[2].x * f, this->rows[2].y * f, this->rows[2].z * f);

	return p2Mat33(this->rows[0], this->rows[1], this->rows[2]);
}

p2Mat33 p2Mat33::operator/(float f)
{
	return p2Mat33(
		p2Vec3(this->rows[0].x / f, this->rows[0].y / f, this->rows[0].z / f),
		p2Vec3(this->rows[1].x / f, this->rows[1].y / f, this->rows[1].z / f),
		p2Vec3(this->rows[2].x / f, this->rows[2].y / f, this->rows[2].z / f)
	);
}

p2Mat33 p2Mat33::operator/=(float f)
{
	this->rows[0] = p2Vec3(this->rows[0].x / f, this->rows[0].y / f, this->rows[0].z / f);
	this->rows[1] = p2Vec3(this->rows[1].x * f, this->rows[1].y * f, this->rows[1].z * f);
	this->rows[2] = p2Vec3(this->rows[2].x / f, this->rows[2].y / f, this->rows[2].z / f);

	return p2Mat33(this->rows[0], this->rows[1], this->rows[2]);
}

p2Mat33 p2Mat33::Invert()
{
	float det = this->GetDeterminant();
	if(det == 0)
		return p2Mat33(this->rows[0], this->rows[1], this->rows[2]);
	else
	{
		p2Mat33 res = this->Transpose();
		// Calculate the adjacent
		res = p2Mat33
		(
			p2Vec3(res.rows[1].y * res.rows[2].z - res.rows[2].y * res.rows[1].z, res.rows[1].x * res.rows[2].z - res.rows[2].x * res.rows[1].z, res.rows[1].x * res.rows[2].y - res.rows[2].x * res.rows[1].y),
			p2Vec3(res.rows[0].y * res.rows[2].z - res.rows[2].y * res.rows[0].z, res.rows[0].x * res.rows[2].z - res.rows[2].x * res.rows[0].z, res.rows[0].x * res.rows[2].y - res.rows[2].x * res.rows[0].y),
			p2Vec3(res.rows[0].y * res.rows[1].z - res.rows[1].y * res.rows[0].z, res.rows[0].x * res.rows[1].z - res.rows[1].x * res.rows[0].z, res.rows[0].x * res.rows[1].y - res.rows[1].x * res.rows[0].y)
		);

		//Apply negativity
		res.rows[0].y = -res.rows[0].y;
		res.rows[1].x = -res.rows[1].x;
		res.rows[1].z = -res.rows[1].z;
		res.rows[2].y = -res.rows[2].y;

		return res / det;
	}
}

p2Mat33 p2Mat33::Transpose()
{
	return p2Mat33(
		p2Vec3(this->rows[0].x, this->rows[1].x, this->rows[2].x),
		p2Vec3(this->rows[0].y, this->rows[1].y, this->rows[2].y),
		p2Vec3(this->rows[0].z, this->rows[1].z, this->rows[2].z)
	);
}

float p2Mat33::GetDeterminant()
{
	return this->rows[0].x *(this->rows[1].y  * this->rows[2].z - this->rows[2].y  * this->rows[1].z) -
		this->rows[0].y *(this->rows[1].x  * this->rows[2].z - this->rows[2].x  * this->rows[1].z) - 
		this->rows[0].z *(this->rows[1].x  * this->rows[2].y - this->rows[2].x  * this->rows[1].y);
}
