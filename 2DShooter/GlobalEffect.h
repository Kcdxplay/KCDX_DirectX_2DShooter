#pragma once
#include "EffectType.h"
#include "BasePart.h"
#include "DirectX.h"

#include<list>

#define Effect GlobalEffect::Instance()

struct BaseEffect
{
	LPDIRECT3DTEXTURE9 texture;
	int startframe;		//��ʼ֡
	int endframe;		//����֡
	int frameW;			//ÿ֡��
	int frameH;			//ÿ֡��
	int columns;		//����
	int delay;			//��ʱ

	void GetEffectDetail(Graphic* graph)
	{
		graph->texture = this->texture;
		graph->startframe = this->startframe;
		graph->endframe = this->endframe;
		graph->frameW = this->frameH;
		graph->frameH = this->frameH;
		graph->columns = this->columns;
		graph->delay = this->delay;
	}
};

class GlobalEffect
{
private:
	list<Graphic> EffectList;	//��Ч��Ⱦ�嵥
	list<Graphic*> RemoveList;	//����˵���Ч
	GlobalEffect() 
	{
		Bootup();
	}

	//���е���Ч��������
	BaseEffect explosion;
	BaseEffect bloodfog;

public:
	static GlobalEffect* Instance();

	void Bootup();

	void Update();
	void Render();

	//�ڵ�ͼĳһ�㣬����ĳ����Ч
	void PlayEffectAt(float x, float y, int effectType);
};
