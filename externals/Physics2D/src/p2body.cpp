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
#include <p2body.h>
#include <p2collider.h>

p2Body::p2Body()
{
}

p2Body::p2Body(p2BodyDef* bodyDef) :
	m_Type(bodyDef->type),
	m_Position(bodyDef->position),
	m_LinearVelocity(bodyDef->linearVelocity),
	m_GravityScale(bodyDef->gravityScale),
	m_Mass(bodyDef->mass)
{
	
}

p2Body::~p2Body()
{
	for (auto collider : m_ColliderList)
		delete(collider);
}
/*-----------------------------------------------------------
					Public functions
-----------------------------------------------------------*/
p2Collider * p2Body::CreateCollider(p2ColliderDef * colliderDef)
{
	p2Collider* collider = new p2Collider(colliderDef, this);
	m_ColliderList.push_back(collider);
	return collider;
}

void p2Body::ApplyForce(p2Vec2 force)
{
	m_Forces += force;
}

void p2Body::AddInContact(p2Contact * contact)
{
	m_ContactList.push_back(contact);
}

void p2Body::RemoveInContact(p2Contact * contact)
{
	m_ContactList.remove(contact);
}

void p2Body::CalculateAABB()
{
	// Reset the current values
	p2Vec2 newBottomLeft = p2Vec2(std::numeric_limits<float>::max(), std::numeric_limits<float>::min());
	p2Vec2 newTopRight = p2Vec2(std::numeric_limits<float>::min(), std::numeric_limits<int>::max());

	if (m_ColliderList.size())
	{
		for (auto col : m_ColliderList)
		{
			p2Shape* shape = col->GetShape();
			if (shape == nullptr)
				continue;

			p2Vec2 colTopRight = shape->GetTopRight();
			p2Vec2 colBotLeft = shape->GetBottomLeft();

			if (newBottomLeft.x > colBotLeft.x)
				newBottomLeft.x = colBotLeft.x;
			if (newBottomLeft.y < colBotLeft.y)
				newBottomLeft.y = colBotLeft.y;

			if (newTopRight.x < colTopRight.x)
				newTopRight.x = colTopRight.x;
			if (newTopRight.y > colTopRight.y)
				newTopRight.y = colTopRight.y;
		}
	}
	else
	{
		newBottomLeft = p2Vec2(0, 0);
		newTopRight = p2Vec2(0, 0);
	}

	m_AABB.bottomLeft = m_Position + newBottomLeft;
	m_AABB.topRight = m_Position + newTopRight;
}

void p2Body::DrawDebugBody(p2Guizmo * guizmoDebug)
{
	guizmoDebug->DrawRect(m_Position, m_AABB.GetExtendsValue(), p2Color(255, 0, 0, 255));
}

/*-----------------------------------------------------------
					Getter and Setters
-----------------------------------------------------------*/
p2Vec2 p2Body::GetLinearVelocity()
{
	return m_LinearVelocity;
}

void p2Body::SetLinearVelocity(p2Vec2 velocity)
{
	m_LinearVelocity = velocity;
}

float p2Body::GetAngularVelocity()
{
	return m_AngularVelocity;
}

float p2Body::GetGravityScale()
{
	return m_GravityScale;
}

p2Vec2 p2Body::GetPosition()
{
	return m_Position;
}

void p2Body::SetPosition(p2Vec2 newPos)
{
	m_Position = newPos;
}

p2BodyType p2Body::GetType()
{
	return m_Type;
}

float p2Body::GetMass()
{
	return m_Mass;
}

p2AABB p2Body::GetAABB()
{
	return m_AABB;
}

std::list<p2Collider*> p2Body::GetColliderList()
{
	return m_ColliderList;
}

p2Vec2 p2Body::GetForces()
{
	return m_Forces;
}

void p2Body::SetForceToZero()
{
	m_Forces = p2Vec2(0, 0);
}

std::list<p2Contact*> p2Body::GetContactList()
{
	return m_ContactList;
}
