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
#include <list>

/*******************************************
*	class p2Contact
*******************************************/
p2Contact::p2Contact(p2Collider * colliderA, p2Collider* colliderB) : m_ColliderA(colliderA), m_ColliderB(colliderB)
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
	return true;
}

p2ContactManager::p2ContactManager()
{
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

	bodyA->AddInContact(contact);
	bodyB->AddInContact(contact);
	m_Listener->BeginContact(contact);
	this->m_ContactList.push_back(contact);
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

}

void p2ContactManager::SetContactListener(p2ContactListener * listener)
{
	this->m_Listener = listener;
}
