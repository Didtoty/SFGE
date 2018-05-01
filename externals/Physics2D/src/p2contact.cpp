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

#include <p2contact.h>
#include <p2shape.h>
#include <list>
#include <cmath>
#include <algorithm>    // std::max

/*******************************************
*	class p2Contact
*******************************************/
p2Contact::p2Contact(p2Collider * colliderA, p2Collider* colliderB) : m_ColliderA(colliderA), m_ColliderB(colliderB)
{
}

p2Contact::~p2Contact()
{
}

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
	//Assomption 2: Resolve with the shape of the collider
	p2Shape* shapeA = m_ColliderA->GetShape();
	p2Shape* shapeB = m_ColliderB->GetShape();

	if (shapeA->GetType() == p2ShapeType::CIRCLE_SHAPE && shapeB->GetType() == p2ShapeType::CIRCLE_SHAPE)
	{
		p2Vec2 deltaCenter = m_ColliderA->GetBody()->GetPosition() - m_ColliderB->GetBody()->GetPosition();
		float deltaR = dynamic_cast<p2CircleShape*>(shapeA)->GetRadius() + dynamic_cast<p2CircleShape*>(shapeB)->GetRadius();
		return deltaCenter.GetMagnitude() <= deltaR;
	}
	else if ((shapeA->GetType() == p2ShapeType::RECTANGLE_SHAPE && shapeB->GetType() == p2ShapeType::RECTANGLE_SHAPE))
	{
		p2Vec2 deltaCenter = m_ColliderA->GetBody()->GetPosition() - m_ColliderB->GetBody()->GetPosition();
		p2Vec2 deltaR = dynamic_cast<p2RectShape*>(shapeA)->GetSize() * 0.5f + dynamic_cast<p2RectShape*>(shapeB)->GetSize() * 0.5f;
		return abs(deltaCenter.x) <= deltaR.x && abs(deltaCenter.y) <= deltaR.y;
	}
	else if ((shapeA->GetType() == p2ShapeType::CIRCLE_SHAPE && shapeB->GetType() == p2ShapeType::RECTANGLE_SHAPE) || 
			(shapeA->GetType() == p2ShapeType::RECTANGLE_SHAPE && shapeB->GetType() == p2ShapeType::CIRCLE_SHAPE))
	{
		p2Vec2 positionCircle, positionRect, sizeRect;
		float radius;

		if (shapeA->GetType() == p2ShapeType::CIRCLE_SHAPE)
		{
			positionCircle = m_ColliderA->GetBody()->GetPosition();
			radius = dynamic_cast<p2CircleShape*>(shapeA)->GetRadius();

			positionRect = m_ColliderB->GetBody()->GetPosition();
			sizeRect = dynamic_cast<p2RectShape*>(shapeB)->GetSize();
		}
		else
		{
			positionCircle = m_ColliderB->GetBody()->GetPosition();
			radius = dynamic_cast<p2CircleShape*>(shapeB)->GetRadius();

			positionRect = m_ColliderA->GetBody()->GetPosition();
			sizeRect = dynamic_cast<p2RectShape*>(shapeA)->GetSize();
		}

		float deltaX = positionCircle.x - std::max(positionRect.x - sizeRect.x * 0.5f, std::min(positionCircle.x, positionRect.x + sizeRect.x * 0.5f));
		float deltaY = positionCircle.y - std::max(positionRect.y - sizeRect.y * 0.5f, std::min(positionCircle.y, positionRect.y + sizeRect.y * 0.5f));
		return (deltaX * deltaX + deltaY * deltaY) < (radius * radius);
	}
	else
	{
		return false;
	}


	//Assomption 1 : All AABB collides
	//return m_ColliderA->GetBody()->GetAABB().Contains(m_ColliderB->GetBody()->GetAABB());
}

p2ContactManager::p2ContactManager()
{
	m_ContactList = std::list<p2Contact*>();
}

/*******************************************
*	class p2ContactManager
*******************************************/
p2ContactManager::p2ContactManager(p2ContactListener* listener) : m_Listener(listener)
{
	m_ContactList = std::list<p2Contact*>();
}

p2ContactManager::~p2ContactManager()
{
	for (auto contact : m_ContactList)
		delete(contact);
}

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

		// Find intersect vector
		p2Vec2 deltaPos = bodyA->GetPosition() - bodyB->GetPosition();
		
		// For each collision...
		for (auto bodyToMove : bodyMovedList)
		{
			// Get smallest axis of the vector FOR CIRCLES
			p2Vec2 forceN = p2Vec2();
			if (bodyToMove == bodyA)
				forceN = deltaPos + bodyB->GetPosition();
			else // bodyToMove == bodyB
				forceN = deltaPos + bodyA->GetPosition();

			// Get normal for RECTANGLES

			// Move the body only in the previously found smallest axis
			bodyToMove->SetLinearVelocity(p2Vec2());
			bodyToMove->ApplyForce(forceN * 100);
		}
	}
}

void p2ContactManager::SetContactListener(p2ContactListener * listener)
{
	this->m_Listener = listener;
}

int p2ContactManager::GetNumContacts()
{
	return m_ContactList.size();
}
