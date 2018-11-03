#include "bhvnode.h"

#include "mathutils.h"
#include <iostream>
#include <algorithm>


BhvNode::BhvNode(Hitable ** list, int n, float time0, float time1)
{
	int axis = int(3 * GetRandomFloat());


	auto boxCmp = [=](const Hitable* a, const Hitable* b)
	{
		Aabb boxLeft, boxRight;
		if (!a->boundingBox(0, 0, boxLeft) || !b->boundingBox(0, 0, boxRight))
		{
			std::cerr << "No bounding box in BhvNode ctor" << std::endl;
		}

		if (boxLeft.GetMin()[axis] - boxRight.GetMin()[axis] < 0.0f)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	};

	std::sort(list, list + n, boxCmp); // TODO: check type cast

	switch(n)
	{
	case 1:
		m_left = m_right = list[0];
		break;
	case 2:
		m_left = list[0];
		m_right = list[1];
		break;
	default:
		int halfOfNumber = n / 2;
		m_left = new BhvNode(list, halfOfNumber, time0, time1);
		m_right = new BhvNode(list + halfOfNumber, n - halfOfNumber, time0, time1);
		break;
	}

	Aabb leftBox, rightBox;

	if (!m_left->boundingBox(time0, time1, leftBox) || !m_right->boundingBox(time0, time1, rightBox))
	{
		std::cerr << "No bounding box in BhvNode ctor" << std::endl;
	}

	m_box = surroundingBox(leftBox, rightBox);
}

BhvNode::BhvNode()
{
}


BhvNode::~BhvNode()
{
}

bool BhvNode::hit(const Ray & ray, float tMin, float tMax, HitRecord & recordOut) const
{
	if(m_box.hit(ray, tMin, tMax))
	{ 
		HitRecord leftRecord, rightRecord;
		bool leftHit = m_left->hit(ray, tMin, tMax, leftRecord);
		bool rightHit = m_left->hit(ray, tMin, tMax, rightRecord);
		bool leftIsClosestHit = leftHit && (!rightHit || leftRecord.t < rightRecord.t);
		bool rightIsClosestHit = rightHit && !leftIsClosestHit;
		if (leftIsClosestHit)
		{
			recordOut = leftRecord;
			return true;
		}
		else if (rightIsClosestHit)
		{
			recordOut = rightRecord;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool BhvNode::boundingBox(float t0, float t1, Aabb & box) const
{
	box = m_box;
	return true;
}
