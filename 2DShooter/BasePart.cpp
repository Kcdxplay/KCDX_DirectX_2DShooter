#include "BasePart.h"
#include <cassert>



int BaseGameEntity::mNextID = 0;

void BaseGameEntity::SetID(int val)
{
	//��֤ID���ڻ����NextID
	assert((val >= mNextID) && "<BaseGameEntity::SetID>: invalid ID");

	mID = val;

	mNextID = mID + 1;
}