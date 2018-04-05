#include "MessageDispatcher.h"
#include "BasePart.h"
#include "EnityManager.h"
#include "CrudeTimer.h"	//粗糙的时间类 作者: Mat Buckland 2002 (fup@ai-junkie.com)

MessageDispatcher* MessageDispatcher::Instance()
{
	static MessageDispatcher instance;
	return &instance;
}

void MessageDispatcher::Discharge(BaseGameEntity * pReceiver, const Telegram & msg)
{
	if (!pReceiver->HandleMessage(msg))
	{
		//没处理消息的相关操作
	}
}

void MessageDispatcher::DispatchMessage(double delay, int sender, int receiver, int msg, void * ExtraInfo)
{
	//获取对应对象的指针
	BaseGameEntity* pSender = EntityMgr->GetEntityByID(sender);
	BaseGameEntity* pReceiver = EntityMgr->GetEntityByID(receiver);

	if (pReceiver == NULL)
	{
		//接收者不可用
		return;
	}

	Telegram telegram(0, sender, receiver, msg, ExtraInfo);

	//是否需要立即发送
	if (delay <= 0)
	{
		Discharge(pReceiver, telegram);
	}

	//如果不是则计算出，何时发送
	else
	{
		double currentTime = Clock->GetCurrentTime();

		telegram.DispatchTime = currentTime + delay;

		//然后丢到延时消息队列里
		PriorityS.insert(telegram);
	}
}

void MessageDispatcher::DispatchDelayedMessages()
{
	double currentTime = Clock->GetCurrentTime();

	//看队列中是否有需要发送的消息，并移除过期的消息
	while (	!PriorityS.empty() &&
			(PriorityS.begin()->DispatchTime < currentTime) &&
			(PriorityS.begin()->DispatchTime > 0))
	{
		Telegram telegram = *PriorityS.begin();

		BaseGameEntity* pReceiver = EntityMgr->GetEntityByID(telegram.Receiver);
		Discharge(pReceiver, telegram);

		PriorityS.erase(PriorityS.begin());
	}
}