#pragma once

#include <map>

#include "DirectX.h"

#define EntityMgr EntityManager::Instance()

class BaseGameEntity;

class EntityManager
{
private:
	typedef std::map<int, BaseGameEntity*> EntityMap;

	EntityMap mEntityMap;
	EntityManager(){}

	EntityManager(const EntityManager&);
	EntityManager& operator= (const EntityManager&);

public:
	//����ǵ���>:3
	static EntityManager* Instance();

	//����һ��ָ��ʵ���ָ�룬����ͼ�к���ID��ʾ��������ٷ���:P
	void RegisterEntity(BaseGameEntity* pEntity);
	//��������ID������ָ���Ӧʵ���ָ��
	BaseGameEntity* GetEntityByID(int id)const;
	//��ͼ���Ƴ�һ��ʵ��
	void RemoveEntity(BaseGameEntity* pEntity);
};