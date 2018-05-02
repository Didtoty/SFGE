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

#ifndef SFGE_P2CONTACT_H
#define SFGE_P2CONTACT_H

#include <p2collider.h>
#include <list>

/**
* \brief Representation of a contact given as argument in a p2ContactListener
*/
class p2Contact
{
public:
	p2Contact(p2Collider* colliderA, p2Collider* colliderB);
	~p2Contact();
	/*-----------------------------------------------------------
						Getter and Setters
	-----------------------------------------------------------*/
	/**
	* \brief Return the collider A
	*/
	p2Collider* GetColliderA();

	/**
	* \brief Return the collider B
	*/
	p2Collider* GetColliderB();

	/**
	* \brief Return the other collider of the contact. If it doesn't match, returns a nullptr
	* \param collider Base collider, to know his neightbor
	*/
	p2Collider* GetOther(p2Collider* collider);

	/**
	* \brief Return true if the two colliders are touching
	*/
	bool isTouching();

private:
	p2Collider* m_ColliderA;
	p2Collider* m_ColliderB;
};

/**
* \brief Listener of contacts happening in an attached p2World
*/
class p2ContactListener
{
public:
	virtual void BeginContact(p2Contact* contact) = 0;
	virtual void EndContact(p2Contact* contact) = 0;
};

/**
* \brief Managing the creation and destruction of contact between colliders
*/
class p2ContactManager
{
public:
	p2ContactManager();
	p2ContactManager(p2ContactListener* listener);
	~p2ContactManager();
	
	/*-----------------------------------------------------------
						Public functions
	-----------------------------------------------------------*/
	/**
	* \brief Add a contact to the contact manager. If it already exists, it will be ignored
	*/
	void AddContact(p2Contact* contact);

	/**
	* \brief Add a list of contacts to the contact manager
	*/
	void AddContacts(std::list<p2Contact*> contacts);

	/**
	* \brief Remove a contact from the contact manager
	*/
	void RemoveContact(p2Contact* contact);

	/**
	* \brief Calculate the resolution of colliding contacts and apply them
	*/
	void ResolveContacts();
		
	/*-----------------------------------------------------------
						Getter and Setters
	-----------------------------------------------------------*/
	/**
	* \brief Set the contact Listener
	*/
	void SetContactListener(p2ContactListener* listener);

	/*-----------------------------------------------------------
						Private vars
	-----------------------------------------------------------*/
private:
	std::list<p2Contact*> m_ContactList;
	p2ContactListener* m_Listener;
};
#endif /* SFGE_P2CONTACT_H */