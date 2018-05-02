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
#include <p2world.h>
#include <p2body.h>
#include <p2quadtree.h>

p2World::p2World(p2Vec2 gravity, p2Guizmo* guizmoDebug) : m_Gravity(gravity), m_GuizmoDebug(guizmoDebug)
{
	m_ContactManager = new p2ContactManager(m_ContactListener);
}

p2World::~p2World()
{
	delete m_ContactManager;

	for (auto body : m_BodyList)
		delete(body);
}

void p2World::Step(float dt)
{
	// Calculate AABB of all bodies
	for (auto body : m_BodyList)
		body->CalculateAABB();

	// -------------------- //
	//		COLLISIONS		//
	// -------------------- //
	p2AABB worldSpace = p2AABB();
	worldSpace.bottomLeft = p2Vec2(0.0f, 800.0f);
	worldSpace.topRight = p2Vec2(1200.0f, 0.0f);

	p2QuadTree* quadTree = new p2QuadTree(0, worldSpace);
	for (auto body : m_BodyList)
	{
		quadTree->Insert(body);
	}

	// Add all the new contacts
	std::list<p2Contact *> contactList;
	quadTree->Retrieve(contactList);
	for (auto contact : contactList)
		m_ContactManager->AddContact(contact);

	delete(quadTree);

	//Update all the contacts and calculate new velocity if needed
	m_ContactManager->ResolveContacts();

	// Update velocity of all bodies and resolve forces
	p2Vec2 aGravity = m_Gravity;
	for (auto body : m_BodyList)
	{
		if (body->GetType() != p2BodyType::STATIC)
		{
			//Acceleration calculus
			p2Vec2 a = aGravity * body->GetGravityScale() + body->GetForces() / body->GetMass();

			//Resolve new velocity
			p2Vec2 v = a * dt + body->GetLinearVelocity();

			//Apply new Velocity and new Position
			body->SetLinearVelocity(v);
			body->SetPosition(v * dt + body->GetPosition());
			//body->SetPosition(a * 0.5f * dt * dt + v * dt + body->GetPosition());

			// Reset all forces
			body->SetForceToZero();
		}
	}
}

p2Body * p2World::CreateBody(p2BodyDef* bodyDef)
{
	p2Body* body = new p2Body(bodyDef);
	m_BodyList.push_back(body);
	return body;
}

void p2World::RemoveBody(p2Body * body)
{
	m_BodyList.remove(body);
	
}

void p2World::SetContactListener(p2ContactListener * contactListener)
{
	this->m_ContactListener = contactListener;
	this->m_ContactManager->SetContactListener(contactListener);
}

void p2World::SetGuizmoDebug(p2Guizmo * guizmoDebug)
{
	m_GuizmoDebug = guizmoDebug;
}

std::list<p2Body*> p2World::GetBodies()
{
	return m_BodyList;
}

int p2World::GetNumContacts()
{
	return m_ContactManager->GetNumContacts();
}

void p2World::DebugDraw()
{
	for(auto body : m_BodyList)
		body->DrawDebugBody(m_GuizmoDebug);
}
