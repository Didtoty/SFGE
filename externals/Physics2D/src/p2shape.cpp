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

#include <p2shape.h>

p2ShapeType p2Shape::GetType()
{
	return m_Type;
}

float p2Shape::GetAngle()
{
	return m_Angle;
}

void p2Shape::SetAngle(float angle)
{
	m_Angle = angle;
}

p2CircleShape::p2CircleShape()
{
	m_Type = p2ShapeType::CIRCLE_SHAPE;
}

p2CircleShape::p2CircleShape(float radius, float angle) : m_Radius(radius)
{
	m_Type = p2ShapeType::CIRCLE_SHAPE;
	m_Angle = angle;
}

void p2CircleShape::SetRadius(float radius)
{
	this->m_Radius = radius;
}

float p2CircleShape::GetRadius()
{
	return this->m_Radius;
}

p2Vec2 p2CircleShape::GetBottomLeft()
{
	return p2Vec2(m_Radius, -m_Radius);
}

p2Vec2 p2CircleShape::GetTopRight()
{
	return p2Vec2(-m_Radius, m_Radius);
}

p2RectShape::p2RectShape()
{
	m_Type = p2ShapeType::RECTANGLE_SHAPE;
}

p2RectShape::p2RectShape(p2Vec2 size, float angle) : m_Size(size)
{
	m_Type = p2ShapeType::RECTANGLE_SHAPE;
	m_Angle = angle;
}

void p2RectShape::SetSize(p2Vec2 size)
{
	this->m_Size = size;
}

p2Vec2 p2RectShape::GetSize()
{
	return this->m_Size;
}

p2Vec2 p2RectShape::GetBottomLeft()
{
	return p2Vec2(-m_Size.x / 2.0f, -m_Size.y / 2.0f);
}

p2Vec2 p2RectShape::GetTopRight()
{
	return p2Vec2(m_Size.x / 2.0f, m_Size.y / 2.0f);
}
