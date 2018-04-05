#include "MessageDispatcher.h"
#include "BasePart.h"
#include "EnityManager.h"
#include "CrudeTimer.h"	//�ֲڵ�ʱ���� ����: Mat Buckland 2002 (fup@ai-junkie.com)

MessageDispatcher* MessageDispatcher::Instance()
{
	static MessageDispatcher instance;
	return &instance;
}

void MessageDispatcher::Discharge(BaseGameEntity * pReceiver, const Telegram & msg)
{
	if (!pReceiver->HandleMessage(msg))
	{
		//û������Ϣ����ز���
	}
}

void MessageDispatcher::DispatchMessage(double delay, int sender, int receiver, int msg, void * ExtraInfo)
{
	//��ȡ��Ӧ�����ָ��
	BaseGameEntity* pSender = EntityMgr->GetEntityByID(sender);
	BaseGameEntity* pReceiver = EntityMgr->GetEntityByID(receiver);

	if (pReceiver == NULL)
	{
		//�����߲�����
		return;
	}

	Telegram telegram(0, sender, receiver, msg, ExtraInfo);

	//�Ƿ���Ҫ��������
	if (delay <= 0)
	{
		Discharge(pReceiver, telegram);
	}

	//�����������������ʱ����
	else
	{
		double currentTime = Clock->GetCurrentTime();

		telegram.DispatchTime = currentTime + delay;

		//Ȼ�󶪵���ʱ��Ϣ������
		PriorityS.insert(telegram);
	}
}

void MessageDispatcher::DispatchDelayedMessages()
{
	double currentTime = Clock->GetCurrentTime();

	//���������Ƿ�����Ҫ���͵���Ϣ�����Ƴ����ڵ���Ϣ
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