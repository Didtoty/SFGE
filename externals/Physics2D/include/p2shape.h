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

#ifndef SFGE_P2SHAPE_H
#define SFGE_P2SHAPE_H

#include <p2vector.h>

/**
* \brief Type of shapes avaliable
*/
enum p2ShapeType {
	NONE,
	RECTANGLE_SHAPE,
	CIRCLE_SHAPE
};

/**
* \brief Abstract representation of a shape
*/
class p2Shape
{
public:
	virtual p2Vec2 GetBottomLeft() = 0;
	virtual p2Vec2 GetTopRight() = 0;
	
	/**
	* \brief Return the type of shape, based on p2SapeType
	*/
	p2ShapeType GetType();

protected:
	p2ShapeType m_Type;
};

/**
* \brief Representation of a circle
*/
class p2CircleShape : public p2Shape
{
public:
	p2CircleShape();
	p2CircleShape(float radius);

	/**
	* \brief Set the radius of the shape
	*/
	void SetRadius(float radius);

	/**
	* \brief Get the radius of the shape
	*/
	float GetRadius();

	/**
	* \brief Get the bottom left position of the shape
	*/
	p2Vec2 GetBottomLeft();

	/**
	* \brief Get the top rightposition of the shape
	*/
	p2Vec2 GetTopRight();
private:
	float m_Radius;
};

/** 
* \brief Representation of a rectangle
*/
class p2RectShape : public p2Shape
{
public:
	p2RectShape();
	p2RectShape(p2Vec2 size);

	/*-----------------------------------------------------------
							Getter and Setters
	-----------------------------------------------------------*/
	/**
	* \brief Set the size of the rectangle shape
	*/
	void SetSize(p2Vec2 size);

	/**
	* \brief Get the size of the rectangle shape
	*/
	p2Vec2 GetSize();

	/**
	* \brief Get the bottom left position of the shape
	*/
	p2Vec2 GetBottomLeft();

	/**
	* \brief Get the top rightposition of the shape
	*/
	p2Vec2 GetTopRight();

	/*-----------------------------------------------------------
							Private vars
	-----------------------------------------------------------*/
private:
	p2Vec2 m_Size;
};

#endif /* SFGE_P2SHAPE_H */