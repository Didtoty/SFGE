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

#define UNSETTED -1

#include <p2contact.h>
#include <p2shape.h>
#include <list>
#include <cmath>
#include <algorithm>    // std::max

#include <iostream>

/*******************************************
*	class p2Contact
*******************************************/
p2Contact::p2Contact(p2Collider * colliderA, p2Collider* colliderB) : m_ColliderA(colliderA), m_ColliderB(colliderB)
{
}

p2Contact::~p2Contact()
{
}
/*-----------------------------------------------------------
					Getter and Setters
-----------------------------------------------------------*/
p2Collider * p2Contact::GetColliderA()
{
	return m_ColliderA;
}

p2Collider * p2Contact::GetColliderB()
{
	return m_ColliderB;
}

p2Collider * p2Contact::GetOther(p2Collider * collider)
{
	if (collider == m_ColliderA)
		return m_ColliderB;
	else if (collider == m_ColliderB)
		return m_ColliderA;
	else
		return nullptr;
}

bool p2Contact::isTouching()
{
	//Assomption 2: Resolve with the shape of the collider without rotation
	p2Shape* shapeA = m_ColliderA->GetShape();
	p2Shape* shapeB = m_ColliderB->GetShape();

	m_CollDiff.distance = UNSETTED;

	if (shapeA->GetType() == p2ShapeType::CIRCLE_SHAPE && shapeB->GetType() == p2ShapeType::CIRCLE_SHAPE)
	{
		p2Vec2 deltaCenter = m_ColliderA->GetBody()->GetPosition() - m_ColliderB->GetBody()->GetPosition();
		float rA = dynamic_cast<p2CircleShape*>(shapeA)->GetRadius();
		float rB = dynamic_cast<p2CircleShape*>(shapeB)->GetRadius();
		if (deltaCenter.GetMagnitude() <= rA + rB)
		{
			m_CollDiff.normal = deltaCenter.Normalized();
			m_CollDiff.distance = (rA + rB) - deltaCenter.GetMagnitude();
		}
	}
	else if ((shapeA->GetType() == p2ShapeType::RECTANGLE_SHAPE && shapeB->GetType() == p2ShapeType::RECTANGLE_SHAPE))
	{
		if (m_ColliderA->GetBody()->GetAngle() == 0 && m_ColliderB->GetBody()->GetAngle() == 0)
		{
			p2Vec2 deltaCenter = m_ColliderA->GetBody()->GetPosition() - m_ColliderB->GetBody()->GetPosition();
			p2Vec2 deltaR = dynamic_cast<p2RectShape*>(shapeA)->GetSize() * 0.5f + dynamic_cast<p2RectShape*>(shapeB)->GetSize() * 0.5f;
			return abs(deltaCenter.x) <= deltaR.x && abs(deltaCenter.y) <= deltaR.y;
		}
		else
		{
			
			m_CollDiff = CalcTouchingSAT(NORMAL_X.ApplyRotation(m_ColliderA->GetBody()->GetAngle()),
										NORMAL_Y.ApplyRotation(m_ColliderA->GetBody()->GetAngle()));

			p2CollisionDiff newColDiff;
			newColDiff = CalcTouchingSAT(NORMAL_X.ApplyRotation(m_ColliderB->GetBody()->GetAngle()),
										NORMAL_Y.ApplyRotation(m_ColliderB->GetBody()->GetAngle()));

			if (m_CollDiff.distance > newColDiff.distance || m_CollDiff.distance == UNSETTED)
				m_CollDiff = newColDiff;
		}
	}
	else if ((shapeA->GetType() == p2ShapeType::CIRCLE_SHAPE && shapeB->GetType() == p2ShapeType::RECTANGLE_SHAPE) || 
			(shapeA->GetType() == p2ShapeType::RECTANGLE_SHAPE && shapeB->GetType() == p2ShapeType::CIRCLE_SHAPE))
	{
		// Make sure collider A is the rectangle
		if (shapeA->GetType() == p2ShapeType::CIRCLE_SHAPE)
		{
			p2Collider* _tempColl = m_ColliderA;
			m_ColliderA = m_ColliderB;
			m_ColliderB = _tempColl;

			shapeA = m_ColliderA->GetShape();
			shapeB = m_ColliderB->GetShape();
		}

		p2Vec2 normal;

		p2Vec2 posRect = m_ColliderA->GetBody()->GetPosition();
		p2Vec2 rectSize = dynamic_cast<p2RectShape*>(shapeA)->GetSize();
		p2Vec2 posCircle = m_ColliderB->GetBody()->GetPosition();
		
		bool rectNormal = true;
		if (posRect.x + rectSize.x * 0.5f > posCircle.x && posCircle.x > posRect.x - rectSize.x * 0.5f)
			normal = NORMAL_X;
		else if (posRect.y + rectSize.y * 0.5f > posCircle.y && posCircle.y > posRect.y - rectSize.y * 0.5f)
			normal = NORMAL_Y;
		else
		{
			normal = (m_ColliderB->GetBody()->GetPosition() - m_ColliderA->GetBody()->GetPosition()).Normalized();
			rectNormal = false;
		}

		if (rectNormal && posRect.x > posCircle.x)
			normal.x = -normal.x;
		if (rectNormal && posRect.y > posCircle.y)
			normal.y = -normal.y;

		// Normal from circle to rectangle
		m_CollDiff = CalcTouchingSAT(normal);

		// Assomption 2 : Basics collisions without rotation
		/* 
		p2Vec2 positionRect = m_ColliderA->GetBody()->GetPosition();
		p2Vec2 sizeRect = dynamic_cast<p2RectShape*>(shapeA)->GetSize();
		p2Vec2 positionCircle = m_ColliderB->GetBody()->GetPosition();
		float radius = dynamic_cast<p2CircleShape*>(shapeB)->GetRadius();

		float deltaX = positionCircle.x - std::max(positionRect.x - sizeRect.x * 0.5f, std::min(positionCircle.x, positionRect.x + sizeRect.x * 0.5f));
		float deltaY = positionCircle.y - std::max(positionRect.y - sizeRect.y * 0.5f, std::min(positionCircle.y, positionRect.y + sizeRect.y * 0.5f));
		return (deltaX * deltaX + deltaY * deltaY) < (radius * radius);
		*/
	}
	else
	{
		return false;
	}


	//std::cout << "distance : " << m_CollDiff.distance << "\n";
	//std::cout << "normal : " << m_CollDiff.normal.x << ", " << m_CollDiff.normal.y << "\n";
	return m_CollDiff.distance > 0.0f;

	//Assomption 1 : All AABB collides
	//return m_ColliderA->GetBody()->GetAABB().Contains(m_ColliderB->GetBody()->GetAABB());
}

p2CollisionDiff p2Contact::GetCollDiff()
{
	return m_CollDiff;
}

float p2Contact::CalculateDistSAT(p2Vec2 normal)
{
	// For all points of Shape A
	std::list<p2Vec2> listPoints = m_ColliderA->GetPoints();
	float minPointA = std::numeric_limits<float>::max();
	float maxPointA = -std::numeric_limits<float>::max();
	for (p2Vec2 pRect : listPoints)
	{
		float projPoint = p2Vec2::Dot(pRect, normal);
		if (minPointA > projPoint)
			minPointA = projPoint;
		if (maxPointA < projPoint)
			maxPointA = projPoint;
	}

	// For all points of Shape B
	float minPointB = std::numeric_limits<float>::max();
	float maxPointB = -std::numeric_limits<float>::max();
	if (m_ColliderB->GetShape()->GetType() == p2ShapeType::RECTANGLE_SHAPE)
	{
		listPoints = m_ColliderB->GetPoints();
		for (p2Vec2 pRect : listPoints)
		{
			float projPoint = p2Vec2::Dot(pRect, normal);
			if (minPointB > projPoint)
				minPointB = projPoint;
			if (maxPointB < projPoint)
				maxPointB = projPoint;
		}
	}
	else // p2ShapeType::CIRCLE_SHAPE
	{
		// Normal inited from circle to rectangle
		// If pos rect
		p2Vec2 posCircle = p2Vec2::Proj(m_ColliderB->GetBody()->GetPosition(), normal);
		float radius = dynamic_cast<p2CircleShape*>(m_ColliderB->GetShape())->GetRadius();

		maxPointB = p2Vec2::Dot(posCircle, normal);
		minPointB = maxPointB - radius;
	}

	float distance = UNSETTED;
	float deltaPoint;

	// Calculate min diff
	if (minPointA >= minPointB)
		deltaPoint = maxPointB - minPointA;
	else
		deltaPoint = maxPointA - minPointB;

	if (deltaPoint >= 0.0f)
		distance = deltaPoint;

	return distance;
}

p2CollisionDiff p2Contact::CalcTouchingSAT(p2Vec2 normal)
{
	float dist = CalculateDistSAT(normal);

	p2CollisionDiff result;

	if (dist > 0.0f)
	{
		result.distance = dist;
		result.normal = normal;
	}
	return result;
}

p2CollisionDiff p2Contact::CalcTouchingSAT(p2Vec2 normalX, p2Vec2 normalY)
{
	float distX = CalculateDistSAT(normalX);
	float distY = CalculateDistSAT(normalY);

	p2CollisionDiff result;

	if (distX >= 0.0f && distY >= 0.0f)
	{
		if (distX < distY)
		{
			result.distance = distX;
			result.normal = normalX;
		}
		else
		{
			result.distance = distY;
			result.normal = normalY;
		}
	}
	return result;
}

/*******************************************
*	class p2ContactManager
*******************************************/
p2ContactManager::p2ContactManager()
{
	m_ContactList = std::list<p2Contact*>();
}

p2ContactManager::p2ContactManager(p2ContactListener* listener) : m_Listener(listener)
{
	m_ContactList = std::list<p2Contact*>();
}

p2ContactManager::~p2ContactManager()
{
	for (auto contact : m_ContactList)
		delete(contact);
}

/*-----------------------------------------------------------
					Public functions
-----------------------------------------------------------*/
void p2ContactManager::AddContact(p2Contact* contact)
{
	p2Collider* colA = contact->GetColliderA();
	p2Collider* colB = contact->GetColliderB();

	p2Body* bodyA = colA->GetBody();
	p2Body* bodyB = colB->GetBody();

	if (bodyA == bodyB)
		return;

	std::list<p2Contact*> contactListB = bodyB->GetContactList();
	for (auto contactB : contactListB) 
	{
		//If it collides well with the right body, and the right collider, that means it already exists
		p2Collider* otherA = contactB->GetOther(colB);
		if (otherA->GetBody() == bodyA && otherA == colA)
		{
			return;
		}
	}

	if (contact->isTouching())
	{
		bodyA->AddInContact(contact);
		bodyB->AddInContact(contact);
		m_Listener->BeginContact(contact);
		this->m_ContactList.push_back(contact);
	}
}

void p2ContactManager::AddContacts(std::list<p2Contact*> contacts)
{
	for(auto contact : contacts)
		this->AddContact(contact);
}

void p2ContactManager::RemoveContact(p2Contact* contact)
{
	contact->GetColliderA()->GetBody()->RemoveInContact(contact);
	contact->GetColliderB()->GetBody()->RemoveInContact(contact);
	m_Listener->EndContact(contact);
	this->m_ContactList.remove(contact);
}

void p2ContactManager::ResolveContacts()
{
	//Check if contacts still touches
	std::list<p2Contact*> contactsToRemove;
	for (auto contact : m_ContactList)
	{
		if (!contact->isTouching())
			contactsToRemove.push_back(contact);
	}

	// Remove the contacts that doesn't touch anymore
	for (auto rContact : contactsToRemove)
	{
		this->RemoveContact(rContact);
		m_ContactList.remove(rContact);
	}

	// TODO: Then resolve contacts
	for (auto contact : m_ContactList)
	{
		p2Body* bodyA = contact->GetColliderA()->GetBody();
		p2Body* bodyB = contact->GetColliderB()->GetBody();

		// Get to know which body is affected by the collision
		std::list<p2Body*> bodyMovedList;
		if (bodyA->GetType() == p2BodyType::DYNAMIC)
			bodyMovedList.push_back(bodyA);
		if (bodyB->GetType() == p2BodyType::DYNAMIC)
			bodyMovedList.push_back(bodyB);
				
		// For each collision...
		for (auto bodyToMove : bodyMovedList)
		{
			p2Vec2 oldVel = bodyToMove->GetLinearVelocity();
			p2Vec2 normal = contact->GetCollDiff().normal;
			p2Vec2 newVel;

			// VERSION QUI MARCHE BIEN ENCORE
			if (normal.x != 0.0f && normal.y != 0.0f)
			{
				newVel.x = oldVel.GetMagnitude() * normal.x;
				newVel.y = oldVel.GetMagnitude() * normal.y;
			}
			else
			{
				if (normal.x != 0)
					newVel.x = oldVel.x * normal.x;
				else
					newVel.x = oldVel.x;

				if (normal.y != 0)
					newVel.y = oldVel.y * normal.y;
				else
					newVel.y = oldVel.y;
			}
			
			bodyToMove->SetLinearVelocity(newVel);

			bodyToMove->SetPosition(bodyToMove->GetPosition() + contact->GetCollDiff().normal * contact->GetCollDiff().distance);
		}
	}
}

/*-----------------------------------------------------------
					Getter and Setters
-----------------------------------------------------------*/
void p2ContactManager::SetContactListener(p2ContactListener * listener)
{
	this->m_Listener = listener;
}
