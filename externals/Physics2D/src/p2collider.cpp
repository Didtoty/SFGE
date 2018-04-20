#include "..\include\p2collider.h"

p2Collider::p2Collider()
{
}

p2Collider::p2Collider(p2ColliderDef* colDef)
	: m_userData(colDef->userData),
	m_shape(colDef->shape),
	m_restitution(colDef->restitution),
	m_isSensor(colDef->isSensor)
{
}

p2Collider::~p2Collider()
{
}

p2Shape * p2Collider::GetShape()
{
	return m_shape;
}

void p2Collider::SetShape(p2Shape* shape)
{
	m_shape = shape;
}

bool p2Collider::IsSensor()
{
	return m_isSensor;
}

void* p2Collider::GetUserData()
{
	return m_userData;
}
