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

bool p2Collider::IsSensor()
{
	return m_isSensor;
}

void* p2Collider::GetUserData()
{
	return m_userData;
}
