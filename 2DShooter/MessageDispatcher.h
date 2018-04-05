#pragma once

#include "Telegram.h"
#include <set>

class BaseGameEntity;

//为了更美好的生活=v=
#define Dispatch MessageDispatcher::Instance()

class MessageDispatcher
{
private:
	//SET用来装延时发送的消息，可以很方便的自动排序，避免重复
	//排序依据为消息的发送时间
	std::set<Telegram> PriorityS;

	//将被发送消息函数调用，创建新的Telegram并调用接收者的接收函数
	void Discharge(BaseGameEntity* pReceiver, const Telegram& msg);

	MessageDispatcher() {}
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);

public:
	//这是一个单例
	static MessageDispatcher* Instance();

	//发送一条消息给其它实体，目标实体用ID来引用
	void DispatchMessage(
		double  delay,		//延迟发送时间
		int    sender,		//发送者ID
		int    receiver,	//接收者ID
		int    msg,			//消息内容
		void*  ExtraInfo);	//附加的额外信息

	//每次游戏循环都会调用
	//发送那些延时发送的消息
	void DispatchDelayedMessages();
};