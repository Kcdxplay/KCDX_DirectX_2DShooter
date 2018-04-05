#include "EnityManager.h"
#include "BasePart.h"

EntityManager * EntityManager::Instance()
{
	static EntityManager instance;
	return &instance;
}

//==========ע��һ��
void EntityManager::RegisterEntity(BaseGameEntity* pEntity)
{
	mEntityMap.insert(std::make_pair(pEntity->ID(), pEntity));
}

//==========���Ҷ���
BaseGameEntity * EntityManager::GetEntityByID(int id) const
{
	//�ҵ���Ӧ��ʵ��
	EntityMap::const_iterator ent = mEntityMap.find(id);

	return ent->second;
}

//==========ɾ������
void EntityManager::RemoveEntity(BaseGameEntity * pEntity)
{
	mEntityMap.erase(mEntityMap.find(pEntity->ID()));
}