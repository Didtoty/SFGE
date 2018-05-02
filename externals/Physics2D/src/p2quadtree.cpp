#include "..\include\p2quadtree.h"

p2QuadTree::p2QuadTree(int nodeLevel, p2AABB bounds) : m_NodeLevel(nodeLevel), m_Bounds(bounds)
{
}

p2QuadTree::~p2QuadTree()
{
	for (int i = 0; i < CHILD_TREE_NMB; i++)
	{
		if (m_Nodes[i] != nullptr)
			delete(m_Nodes[i]);
	}
}

void p2QuadTree::Clear()
{
}

void p2QuadTree::Split()
{
	/******************************
	* How the nodes are separated :
	*_______________
	*|0		|1		|	Axis :
	*|______|_______|	|---->x
	*|2		|3		|	|
	*|______|_______|	\/y
	******************************/

	if (m_Nodes[0] == nullptr)
	{
		p2AABB newBounds;
		// Node 0
		newBounds.bottomLeft = m_Bounds.GetCenter() - p2Vec2(m_Bounds.GetExtendsValue().x, 0.0f);
		newBounds.topRight = m_Bounds.GetCenter() - p2Vec2(0.0f, m_Bounds.GetExtendsValue().y);
		m_Nodes[0] = new p2QuadTree(m_NodeLevel + 1, newBounds);

		// Node 1
		newBounds.bottomLeft = m_Bounds.GetCenter();
		newBounds.topRight = m_Bounds.topRight;
		m_Nodes[1] = new p2QuadTree(m_NodeLevel + 1, newBounds);

		// Node 2
		newBounds.bottomLeft = m_Bounds.bottomLeft;
		newBounds.topRight = m_Bounds.GetCenter();
		m_Nodes[2] = new p2QuadTree(m_NodeLevel + 1, newBounds);

		// Node 3
		newBounds.bottomLeft = m_Bounds.GetCenter() + p2Vec2(0.0f, m_Bounds.GetExtendsValue().y);
		newBounds.topRight = m_Bounds.GetCenter() + p2Vec2(m_Bounds.GetExtendsValue().x, 0.0f);
		m_Nodes[3] = new p2QuadTree(m_NodeLevel + 1, newBounds);
	}

	// Insert all our bodies to the next levels
	std::list<p2Body*> movedBodies;
	for(auto body : m_Bodies)
	{
		int index = GetIndex(body);
		if (index != -1) 
		{
			m_Nodes[index]->Insert(body);
			movedBodies.push_back(body);
		}
	}

	for (auto body : movedBodies)
	{
		m_Bodies.remove(body);
	}
}

int p2QuadTree::GetIndex(p2Body * body)
{
	int index = -1;
	int numCollides = 0;
	for (int i = 0; i <= CHILD_TREE_NMB; i++)
	{
		if (m_Nodes[i]->m_Bounds.Contains(body->GetAABB()))
		{
			index = i;
			numCollides++;
		}
	}
	if ((index <= -1 && index >= CHILD_TREE_NMB) || numCollides != 1)
		return -1;
	else
		return index;
}

void p2QuadTree::Insert(p2Body * body)
{
	m_Bodies.push_back(body);

	if (m_Bodies.size() > MAX_OBJECTS && m_NodeLevel < MAX_LEVELS)
	{
		Split();
	}
}

void p2QuadTree::Retrieve(std::list<p2Contact *>& contactList)
{
	if (m_Nodes[0] == nullptr)
	{
		if (m_Bodies.size() > 1)
		{
			auto objItr = m_Bodies.begin();
			auto objSecondItr = m_Bodies.begin();

			while (objItr != m_Bodies.end())
			{
				objSecondItr = objItr;
				objSecondItr++;
				while (objSecondItr != m_Bodies.end())
				{
					if ((*objItr)->GetAABB().Contains((*objSecondItr)->GetAABB()))
					{			
						for(auto firstCollider : (*objItr)->GetColliderList())
						{
							for (auto secondCollider : (*objSecondItr)->GetColliderList())
							{
								contactList.push_back(new p2Contact(firstCollider, secondCollider));
							}
						}
					}
					objSecondItr++;
				} // end while
				objItr++;
			} // end while
		} // end if
	}
	else
	{
		for(int i = 0; i < CHILD_TREE_NMB; i++)
		{
			m_Nodes[i]->Retrieve(contactList);
		}
	}
}

void p2QuadTree::DebugDraw(p2Guizmo * guizmoDebug)
{
	//Draw basic rect
	//    _4_
	//  1|   |3
	//   |_2_|
	guizmoDebug->DrawLine(m_Bounds.bottomLeft, p2Vec2(m_Bounds.bottomLeft.x, m_Bounds.topRight.y), p2Color(0, 255, 255, 255)); // 1
	guizmoDebug->DrawLine(m_Bounds.bottomLeft, p2Vec2(m_Bounds.topRight.x, m_Bounds.bottomLeft.y), p2Color(0, 255, 255, 255)); // 2
	guizmoDebug->DrawLine(m_Bounds.topRight, p2Vec2(m_Bounds.topRight.x, m_Bounds.bottomLeft.y), p2Color(0, 255, 255, 255)); // 3
	guizmoDebug->DrawLine(m_Bounds.topRight, p2Vec2(m_Bounds.bottomLeft.x, m_Bounds.topRight.y), p2Color(0, 255, 255, 255)); // 4

	if (m_Nodes[0] != nullptr)
	{
		for (int i = 0; i < CHILD_TREE_NMB; i++)
		{
			m_Nodes[i]->DebugDraw(guizmoDebug);
		}
	}
}
