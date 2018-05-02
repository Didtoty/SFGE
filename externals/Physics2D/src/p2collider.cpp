#include "..\include\p2collider.h"

p2Collider::p2Collider(p2ColliderDef* colDef, p2Body* body) :
	m_userData(colDef->userData),
	m_restitution(colDef->restitution),
	m_isSensor(colDef->isSensor),
	m_AttachedBody(body)
{
	switch (colDef->shape->GetType())
	{
	case p2ShapeType::CIRCLE_SHAPE:
		m_shape = new p2CircleShape(dynamic_cast<p2CircleShape*>(colDef->shape)->GetRadius());
		break;
	case p2ShapeType::RECTANGLE_SHAPE:
		m_shape = new p2RectShape(dynamic_cast<p2RectShape*>(colDef->shape)->GetSize());
		break;
	}
}

p2Collider::~p2Collider()
{
	if (m_shape != nullptr)
		delete(m_shape);
}

/*-----------------------------------------------------------
					Getter and Setters
-----------------------------------------------------------*/
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

p2Body * p2Collider::GetBody()
{
	return m_AttachedBody;
}