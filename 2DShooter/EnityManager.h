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
	//这个是单例>:3
	static EntityManager* Instance();

	//储存一个指向实体的指针，丢在图中后用ID表示，方便快速访问:P
	void RegisterEntity(BaseGameEntity* pEntity);
	//根据所给ID，返回指向对应实体的指针
	BaseGameEntity* GetEntityByID(int id)const;
	//从图中移除一个实体
	void RemoveEntity(BaseGameEntity* pEntity);
};