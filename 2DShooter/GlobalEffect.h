#pragma once
#include "EffectType.h"
#include "BasePart.h"
#include "DirectX.h"

#include<list>

#define Effect GlobalEffect::Instance()

struct BaseEffect
{
	LPDIRECT3DTEXTURE9 texture;
	int startframe;		//开始帧
	int endframe;		//结束帧
	int frameW;			//每帧宽
	int frameH;			//每帧高
	int columns;		//列数
	int delay;			//延时

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
	list<Graphic> EffectList;	//特效渲染清单
	list<Graphic*> RemoveList;	//完成了的特效
	GlobalEffect() 
	{
		Bootup();
	}

	//所有的特效丢到这里
	BaseEffect explosion;
	BaseEffect bloodfog;

public:
	static GlobalEffect* Instance();

	void Bootup();

	void Update();
	void Render();

	//在地图某一点，播放某个特效
	void PlayEffectAt(float x, float y, int effectType);
};
