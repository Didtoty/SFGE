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

p2Contact::p2Contact(p2Collider * colliderA, p2Collider* colliderB) : m_colliderA(colliderA), m_colliderB(colliderB)
{
}

p2Collider * p2Contact::GetColliderA()
{
	return m_colliderA;
}

p2Collider * p2Contact::GetColliderB()
{
	return m_colliderB;
}

bool p2Contact::isTouching()
{
	return true;
}

p2ContactManager::p2ContactManager()
{
	m_ContactList = std::list<p2Contact*>();
}

p2ContactManager::~p2ContactManager()
{
}

void p2ContactManager::AddContact(p2Contact* contact)
{
	this->m_ContactList.push_back(contact);
}

void p2ContactManager::AddContacts(std::list<p2Contact*> contacts)
{
	this->m_ContactList.merge(contacts);
}

void p2ContactManager::RemoveContact(p2Contact* contact)
{
	this->m_ContactList.remove(contact);
}

void p2ContactManager::ResolveContacts(p2ContactListener* listener)
{

}
