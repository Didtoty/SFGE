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


#ifndef SFGE_P2COLLIDER_H
#define SFGE_P2COLLIDER_H

#include <p2shape.h>
#include <p2body.h>
#include <p2vector.h>

#include <list>

/**
* \brief Struct defining a p2Collider when creating one
*/
struct p2ColliderDef
{
	void* userData;
	p2Shape* shape;
	float bounciness;
	bool isSensor;
	p2Vec2 offset = p2Vec2();
};

/**
* \brief Representation of a Collider attached to a p2Body
*/
class p2Collider
{
public:
	p2Collider(p2ColliderDef* colDef, p2Body* body);
	~p2Collider();

	/*-----------------------------------------------------------
						Getter and Setters
	-----------------------------------------------------------*/
	/**
	* \brief Return a pointer of the current shape
	*/
	p2Shape* GetShape();

	/**
	* \brief Set the current shape
	*/
	void SetShape(p2Shape* shape);

	/**
	* \brief Check if the p2Collider is a sensor
	*/
	bool IsSensor();
	/**
	* \brief Return the userData
	*/
	void* GetUserData();

	/**
	* \brief Return the body that the shape is attached to
	*/
	p2Body* GetBody();

	/**
	* \brief Get the local angle of the collider
	*/
	float GetLocalAngle();

	/**
	* \brief Get the global angle of the collider
	*/
	float GetGlobalAngle();

	/**
	* \brief Get the offset of the collider from the body
	*/
	p2Vec2 GetOffset();

	/**
	* \brief Calculate and return a list of the points defining the rectangle
	*/
	std::list<p2Vec2> GetPoints();

	/*-----------------------------------------------------------
							Private vars
	-----------------------------------------------------------*/
private:
	void* m_UserData;
	p2Shape* m_Shape;
	float m_Bounciness;
	bool m_IsSensor;

	p2Body* m_AttachedBody;
	p2Vec2 m_Offset;
};
#endif /* SFGE_P2COLLIDER_H */