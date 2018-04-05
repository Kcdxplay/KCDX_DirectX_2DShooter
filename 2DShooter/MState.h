#pragma once

struct Telegram;
class CharcterDetailData;
class Graphic;

template <typename type>
class MState	//MotionState运动状态
{
public:
	CharcterDetailData* pData;
	Graphic* pGraph;

	virtual void Enter(type*) = 0;		//进入状态的操作
	virtual void Execute(type*) = 0;	//执行状态具体操作
	virtual void Exit(type*) = 0;		//退出状态的操作

	//如果收到了发送器发送的消息，这个函数将被调用
	virtual bool OnMessage(type*, const Telegram&) = 0;

	virtual ~MState() {}
};