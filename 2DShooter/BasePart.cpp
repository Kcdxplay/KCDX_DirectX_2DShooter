#include "BasePart.h"
#include <cassert>



int BaseGameEntity::mNextID = 0;

void BaseGameEntity::SetID(int val)
{
	//保证ID大于或等于NextID
	assert((val >= mNextID) && "<BaseGameEntity::SetID>: invalid ID");

	mID = val;

	mNextID = mID + 1;
}