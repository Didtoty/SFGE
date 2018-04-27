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

#ifndef SFGE_P2BODY_H
#define SFGE_P2BODY_H

#include <p2aabb.h>
#include <list>
#include <p2guizmo.h>

class p2Collider;
class p2Contact;
struct p2ColliderDef;

enum class p2BodyType
{
	STATIC,
	KINEMATIC,
	DYNAMIC
};

/**
* \brief Struct Defining the p2Body when creating it
*/
struct p2BodyDef
{
	p2BodyType type;
	p2Vec2 position;
	p2Vec2 linearVelocity;
	float gravityScale;
	float mass;
};

// ADD LIST OF COLLIDERS

/**
* \brief Rigidbody representation
*/
class p2Body
{
public:
	p2Body();
	p2Body(p2BodyDef* bodyDef);
	~p2Body();

	/**
	* \brief Factory method creating a p2Collider
	* \param colliderDef p2ColliderDef definition of the collider
	* \return p2Collider collider attached to the p2Body
	*/
	p2Collider* CreateCollider(p2ColliderDef* colliderDef);

	/**
	* \brief Add a force to the body, applied in his center
	* \param force The force to apply to the body
	*/
	void ApplyForce(p2Vec2 force);

	/**
	* \brief Add a contact to the body.
	*/
	void AddInContact(p2Contact* contact);

	/**
	* \brief Remove a contact to the body.
	*/
	void RemoveInContact(p2Contact* contact);

	/**
	* \brief Calculate the AABB of the body.
	*/
	void CalculateAABB();

	/************************
	* Getters and Setters
	************************/

	/**
	* \brief Return the Linear Velocity of the body
	*/
	p2Vec2 GetLinearVelocity();

	/**
	* \brief Set the Linear Velocity of the body
	*/
	void SetLinearVelocity(p2Vec2 velocity);

	/**
	* \brief Return the Angular Velocity of the body
	*/
	float GetAngularVelocity();

	/**
	* \brief Get the Gravity Scale of the body
	*/
	float GetGravityScale();

	/**
	* \brief Get the Position of the body
	*/
	p2Vec2 GetPosition();

	/**
	* \brief Set the Position of the body
	*/
	void SetPosition(p2Vec2 newPos);

	/**
	* \brief Get the Type of the body, based on p2BodyType
	*/
	p2BodyType GetType();

	/**
	* \brief Get the mass of the body
	*/
	float GetMass();

	/**
	* \brief Get the AABB of the body
	*/
	p2AABB GetAABB();

	/**
	* \brief Get the list of colliders attached to the body
	*/
	std::list<p2Collider*> GetColliderList();

	/**
	* \brief Get the forces applies in this frame to the body
	*/
	p2Vec2 GetForces();

	/**
	* \brief Reset all the forces added previously to the body this frame
	*/
	void SetForceToZero();

	/**
	* \brief Get the list of contacts involving this body
	*/
	std::list<p2Contact*> GetContactList();

	void DrawDebugBody(p2Guizmo* guizmoDebug);
private:
	p2AABB m_AABB;
	p2BodyType m_Type;
	p2Vec2 m_Position;
	p2Vec2 m_LinearVelocity;
	float m_AngularVelocity;
	float m_GravityScale;
	float m_Mass;
	p2Vec2 m_Forces;

	std::list<p2Collider*> m_ColliderList;
	std::list<p2Contact*> m_ContactList;
};

#endif