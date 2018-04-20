#include "..\include\p2quadtree.h"

p2QuadTree::p2QuadTree(int nodeLevel, p2AABB bounds)
{
}

p2QuadTree::~p2QuadTree()
{
}

void p2QuadTree::Clear()
{
}

void p2QuadTree::Split()
{
}

int p2QuadTree::GetIndex(p2Body * rect)
{
	return 0;
}

void p2QuadTree::Insert(p2Body * obj)
{
	m_Objects.push_back(obj);
}

std::list<p2Contact *> p2QuadTree::Retrieve()
{
	std::list<p2Contact *> contactList;
	//if (nodes[0] == nullptr)
	//{
		if (m_Objects.size() > 1)
		{
			auto objItr = m_Objects.begin();
			auto objSecondItr = m_Objects.begin();

			while (objItr != m_Objects.end())
			{
				objSecondItr = objItr;
				objSecondItr++;
				while (objSecondItr != m_Objects.end())
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
	/*
	}
	else
	{
		// Add children contacts
		for (int i = 0; i < CHILD_TREE_NMB; i++)
		{
			auto contactListChildren = nodes[i]->Retrieve();
			contactList.insert(contactList.end(), contactListChildren.begin(), contactListChildren.begin());
		}

		//Retrieve all parents objects
		for (auto objItr = m_Objects.begin(); objItr != m_Objects.end(); objItr++)
		{
			for (int i = 0; i < CHILD_TREE_NMB; i++)
			{
				for (auto childObjItr = nodes[i]->m_Objects.begin(); childObjItr != m_Objects.end(); childObjItr++) 
				{
					if ((*objItr)->GetAABB().Contains((*childObjItr)->GetAABB()))
					{			
						auto contListItr = (*objItr)->GetColliderList().begin();
						auto contListChildItr = (*childObjItr)->GetColliderList().begin();
						while(contListItr != (*objItr)->GetColliderList().end())
						{
							while (contListChildItr != (*childObjItr)->GetColliderList().end())
							{
								contactList.push_back(p2Contact(*contListItr, *contListChildItr));
								contListChildItr++;
							}
							contListItr++;
						} // end while
					} // end if
				} // end for
			} // end for
		} // end for
	}
	*/
	return contactList;
}
