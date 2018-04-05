#pragma once
#include "DirectX.h"

struct Telegram;

class BaseGameEntity
{
private:
	int mID;	//游戏体对应ID
	static int mNextID;	//下一个有效ID

	void SetID(int val);

public:
	BaseGameEntity(){}
	BaseGameEntity(int id)
	{
		SetID(id);
	}

	//相关处理函数
	virtual void Update() = 0;
	virtual void Render() = 0;

	//消息接收机制
	virtual bool HandleMessage(const Telegram& msg) = 0;

	int ID() const { return mID; }
};

class Graphic	//图像模块
{
public:
	LPDIRECT3DTEXTURE9 texture;	//贴图
	
	D3DXVECTOR3 paintPos;		//屏幕绘制位置
	D3DXVECTOR2 mapPos;			//地图相对位置
	D3DXVECTOR2 scale;			//缩放
	D3DXVECTOR2 center;			//缩放中心
	D3DXVECTOR2 trans;			//X，Y的位置
	double rotation;			//旋转角度
	//D3DXVECTOR2 direction;	//朝向
	D3DXMATRIX TransMat;		//缩放比例等
	bool towards;				//绘制朝向	False-向左  True-向右

	//----------精灵表部分
	int frameW;					//每帧宽度
	int frameH;					//每帧高度
	int frameNum;				//现在是第几帧
	int startframe;				//从第几帧开始
	int endframe;				//到第几帧结束
	int columns;				//精灵表列数
	int delay;					//精灵每帧延时

	int lastTime = GetTickCount();	//上次绘制时间

	//void spriteGoOn()
	//{
	//	if (GetTickCount() > lastTime + delay)
	//	{

	//	}
	//}
	//
	bool operator==(const Graphic &graph)
	{
		return (&graph == this);
	}
};


//用于初始化一个游戏角色
template <typename type>
class CharcterTypeSet
{
public:
	virtual void SetCharcterData(type*) = 0;

	virtual ~CharcterTypeSet() {}
};

struct RC_DetailInfo
{
	int rectType;
	int ID;
};
//优化子弹碰撞判断，存储碰撞相关信息
struct RectCollision
{
	RECT mainRect;			//矩阵主体
	D3DXVECTOR2 collisionPoint;	//碰撞坐标
	RC_DetailInfo extraInfo;//额外信息
};

enum RectType
{
	WallRect,
	EnemyRect
};

////消息结构体
//struct Telegram
//{
//	//发送者实体
//	int Sender;
//	//接收者实体
//	int Receiver;
//	//信息本身
//	int Msg;
//	
//	//延时时间
//	double DispatchTime;
//	//可能会有的额外消息
//	void* ExtraInfo;
//
//	Telegram():	DispatchTime(-1),
//				Sender(-1),
//				Receiver(-1),
//				Msg(-1)
//	{}
//	Telegram(	double time,
//				int    sender,
//				int    receiver,
//				int    msg,
//				void*  info = NULL) : DispatchTime(time),
//				Sender(sender),
//				Receiver(receiver),
//				Msg(msg),
//				ExtraInfo(info)
//	{}
//};