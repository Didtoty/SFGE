#include "..\include\p2collider.h"

p2Collider::p2Collider(p2ColliderDef* colDef, p2Body* body) :
	m_UserData(colDef->userData),
	m_Bounciness(colDef->bounciness),
	m_IsSensor(colDef->isSensor),
	m_Offset(colDef->offset),
	m_AttachedBody(body)
{
	switch (colDef->shape->GetType())
	{
	case p2ShapeType::CIRCLE_SHAPE:
		m_Shape = new p2CircleShape(dynamic_cast<p2CircleShape*>(colDef->shape)->GetRadius());
		break;
	case p2ShapeType::RECTANGLE_SHAPE:
		m_Shape = new p2RectShape(dynamic_cast<p2RectShape*>(colDef->shape)->GetSize());
		break;
	}
}

p2Collider::~p2Collider()
{
	if (m_Shape != nullptr)
		delete(m_Shape);
}

/*-----------------------------------------------------------
					Getter and Setters
-----------------------------------------------------------*/
p2Shape * p2Collider::GetShape()
{
	return m_Shape;
}

void p2Collider::SetShape(p2Shape* shape)
{
	m_Shape = shape;
}

bool p2Collider::IsSensor()
{
	return m_IsSensor;
}

void* p2Collider::GetUserData()
{
	return m_UserData;
}

p2Body * p2Collider::GetBody()
{
	return m_AttachedBody;
}

p2Vec2 p2Collider::GetOffset()
{
	return m_Offset;
}

std::list<p2Vec2> p2Collider::GetPoints()
{
	std::list<p2Vec2> listPoints = std::list<p2Vec2>();
	if (m_Shape->GetType() == p2ShapeType::CIRCLE_SHAPE)
	{
		listPoints.push_back((m_AttachedBody->GetPosition() + m_Offset).ApplyRotation(m_AttachedBody->GetAngle()));
	} 
	else if (m_Shape->GetType() == p2ShapeType::RECTANGLE_SHAPE)
	{
		p2Vec2 size = dynamic_cast<p2RectShape*>(m_Shape)->GetSize() * 0.5f;
		
		p2Vec2 colPosition = m_AttachedBody->GetPosition() + m_Offset;
		colPosition.ApplyRotation(m_AttachedBody->GetAngle());

		listPoints.push_back(colPosition - size);
		listPoints.push_back(colPosition + p2Vec2(-size.x, size.y));
		listPoints.push_back(colPosition + size);
		listPoints.push_back(colPosition + p2Vec2(size.x, -size.y));
	}

	return listPoints;
}

void p2Collider::DrawDebug(p2Guizmo * guizmoDebug)
{
	if (m_Shape->GetType() == p2ShapeType::CIRCLE_SHAPE)
	{
		guizmoDebug->DrawCircle(m_AttachedBody->GetPosition() + m_Offset, dynamic_cast<p2CircleShape*>(m_Shape)->GetRadius(), p2Color(0,0,0,0), 1.0f, p2Color(0, 125, 0, 125));
	}
	if (m_Shape->GetType() == p2ShapeType::RECTANGLE_SHAPE)
	{
		guizmoDebug->DrawRect(m_AttachedBody->GetPosition() + m_Offset, dynamic_cast<p2RectShape*>(m_Shape)->GetSize(), p2Color(0, 0, 0, 0), 1.0f, p2Color(125, 0, 125, 125));
	}
}