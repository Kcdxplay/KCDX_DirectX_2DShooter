#include "GlobalEffect.h"
#include "Map.h"

GlobalEffect * GlobalEffect::Instance()
{
	static GlobalEffect instance;
	return &instance;
}

void GlobalEffect::Update()
{
	for (auto& var : EffectList)
	{
		MAP->GetPaintPos(var.mapPos.x, var.mapPos.y, &var.paintPos.x, &var.paintPos.y);
	}
	for (auto& var : RemoveList)
	{
		EffectList.remove(*var);
	}
	RemoveList.clear();
}

void GlobalEffect::Render()
{
	for (auto& var : EffectList)
	{
		spriteOBJ->Begin(D3DXSPRITE_ALPHABLEND);
		Sprite_Animate(var.frameNum, var.startframe, var.endframe, var.lastTime, var.delay);
		Sprite_Draw_Frame(var.texture, &var.paintPos, var.frameNum, var.frameW, var.frameH, var.columns);
		spriteOBJ->End();

		if (var.frameNum == var.endframe)
		{
			RemoveList.push_back(&var);
		}
	}
}

void GlobalEffect::PlayEffectAt(float x, float y, int effectType)
{
	Graphic graph;
	graph.mapPos.x = x;
	graph.mapPos.y = y;
	graph.frameNum = 0;

	switch (effectType)
	{
	case Eft_Explosion:
		explosion.GetEffectDetail(&graph);
		break;
	case Eft_BloodFog:
		bloodfog.GetEffectDetail(&graph);
		break;
	default:
		break;
	}

	graph.mapPos.x -= graph.frameW / 2;
	graph.mapPos.y -= graph.frameH / 2;

	MAP->GetPaintPos(graph.mapPos.x, graph.mapPos.y, &graph.paintPos.x, &graph.paintPos.y);

	EffectList.push_front(graph);
}

void GlobalEffect::Bootup()
{
	//explosion部分
	explosion.texture= LoadTextureNoInfo(L"explosion_30_128.png");
	explosion.startframe = 0;
	explosion.endframe = 29;
	explosion.delay = 10;
	explosion.frameH = 128;
	explosion.frameW = 128;
	explosion.columns = 6;

	//bloodfog部分
}