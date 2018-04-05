#include "EnityManager.h"
#include "BasePart.h"

EntityManager * EntityManager::Instance()
{
	static EntityManager instance;
	return &instance;
}

//==========注册一下
void EntityManager::RegisterEntity(BaseGameEntity* pEntity)
{
	mEntityMap.insert(std::make_pair(pEntity->ID(), pEntity));
}

//==========查找对象
BaseGameEntity * EntityManager::GetEntityByID(int id) const
{
	//找到对应的实体
	EntityMap::const_iterator ent = mEntityMap.find(id);

	return ent->second;
}

//==========删除对象
void EntityManager::RemoveEntity(BaseGameEntity * pEntity)
{
	mEntityMap.erase(mEntityMap.find(pEntity->ID()));
}