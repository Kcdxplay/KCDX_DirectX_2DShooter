#include "Charcter.h"
#include "DirectX.h"
#include "Map.h"

void Charcter::LoadTexture(wstring file, D3DCOLOR color)
{
	D3DXIMAGE_INFO info;

	graph.texture = LoadTextureWithInfo(file, color, &info);

	graph.frameW = info.Width;
	graph.frameH = info.Height;
	graph.columns = 1;
	
	rect = { 0,0,long(info.Width) ,long(info.Height) };
	RectSet();

	if (pWeapon)
	{
		pWeapon->LoadTexture();
	}
}
void Charcter::LoadTexture(wstring file, float framW, float framH, D3DCOLOR color)
{
	graph.texture = LoadTextureNoInfo(file, color);

	rect = { 0,0,long(framW),long(framH) };
	RectSet();
}

void Charcter::RectSet()
{
	float width = rect.right - rect.left;
	float height = rect.bottom - rect.top;
	
	rect.left = graph.mapPos.x;
	rect.top = graph.mapPos.y;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	preCheck[0] = { rect.left - 10,rect.top,rect.left,rect.bottom - 5 };
	preCheck[1] = { rect.right,rect.top,rect.right + 10,rect.bottom - 5 };
	preCheck[2] = { rect.left,rect.bottom,rect.right,rect.bottom + 10 };
}

RECT Charcter::GetMainRect()
{
	return rect;
}
RECT Charcter::GetPreCheckRect(int num)
{
	return preCheck[num];
}

void Charcter::BootUp(float x, float y, int type)
{
	graph.mapPos.x = x;
	graph.mapPos.y = y;

	Map::Instance()->GetPaintPos(x, y, &graph.paintPos.x, &graph.paintPos.y);

	switch (type)
	{
	case 1:
		C_Normal::Instance()->SetCharcterData(this);
		break;
	case 2:
		C_Fast::Instance()->SetCharcterData(this);
		break;
	case 3:
		C_Heavy::Instance()->SetCharcterData(this);
		break;
	default:
		break;
	}

	Map::Instance()->GetPaintPos(graph.mapPos.x, graph.mapPos.y, &graph.paintPos.x, &graph.paintPos.y);
}

void Charcter::SetPos(float x, float y)
{
	graph.mapPos.x = x;
	graph.mapPos.y = y;

	Map::Instance()->GetPaintPos(graph.mapPos.x, graph.mapPos.y, &graph.paintPos.x, &graph.paintPos.y);
}
void Charcter::SetHealth(float health)
{
	this->health = health;
}

bool Charcter::HandleMessage(const Telegram & msg)
{
	return pMStateMachine->HandleMessage(msg);
}

void Charcter::Update()
{
	static CharcterDetailData* pData = GetDetailData();
	static Graphic* pGraph = GetGraphic();

	pMStateMachine->Update();

	RectSet();

	if (!Map::Instance()->CheckWallCollision(preCheck[2]))
	{
		pMStateMachine->ChangeState(MFalling::Instance());
	}

	Map::Instance()->GetPaintPos(
		pGraph->mapPos.x,
		pGraph->mapPos.y,
		&pGraph->paintPos.x,
		&pGraph->paintPos.y);
}

void Charcter::Render()
{
	spriteOBJ->Begin(D3DXSPRITE_ALPHABLEND);
	spriteOBJ->Draw(graph.texture, NULL, NULL, &graph.paintPos, D3DCOLOR_XRGB(255, 255, 255));
	spriteOBJ->End();
}

void Charcter::GotHited(float damage)
{
	health -= damage;
}