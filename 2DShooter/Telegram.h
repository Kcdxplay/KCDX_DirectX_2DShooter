#pragma once
#include "DirectX.h"

struct Telegram
{
	//发送者ID
	int          Sender;

	//接收者ID
	int          Receiver;

	//消息本身
	//消息都在MessageType.h中被定义
	int          Msg;

	//消息延时发送时间
	//该消息应被发送的具体时间
	double       DispatchTime;

	//所有可能用到的附加信息放到这里
	void*        ExtraInfo;


	Telegram() :DispatchTime(-1),
		Sender(-1),
		Receiver(-1),
		Msg(-1)
	{}


	Telegram(double time,
		int    sender,
		int    receiver,
		int    msg,
		void*  info = NULL) : DispatchTime(time),
		Sender(sender),
		Receiver(receiver),
		Msg(msg),
		ExtraInfo(info)
	{}
};
const double SmallestDelay = 0.25;


inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return (fabs(t1.DispatchTime - t2.DispatchTime) < SmallestDelay) &&
		(t1.Sender == t2.Sender) &&
		(t1.Receiver == t2.Receiver) &&
		(t1.Msg == t2.Msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)
	{
		return false;
	}

	else
	{
		return  (t1.DispatchTime < t2.DispatchTime);
	}
}

template <class T>
inline T DereferenceToType(void* p)
{
	return *(T*)(p);
}
