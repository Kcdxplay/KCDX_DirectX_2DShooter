#pragma once

#include "Telegram.h"
#include <set>

class BaseGameEntity;

//Ϊ�˸����õ�����=v=
#define Dispatch MessageDispatcher::Instance()

class MessageDispatcher
{
private:
	//SET����װ��ʱ���͵���Ϣ�����Ժܷ�����Զ����򣬱����ظ�
	//��������Ϊ��Ϣ�ķ���ʱ��
	std::set<Telegram> PriorityS;

	//����������Ϣ�������ã������µ�Telegram�����ý����ߵĽ��պ���
	void Discharge(BaseGameEntity* pReceiver, const Telegram& msg);

	MessageDispatcher() {}
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);

public:
	//����һ������
	static MessageDispatcher* Instance();

	//����һ����Ϣ������ʵ�壬Ŀ��ʵ����ID������
	void DispatchMessage(
		double  delay,		//�ӳٷ���ʱ��
		int    sender,		//������ID
		int    receiver,	//������ID
		int    msg,			//��Ϣ����
		void*  ExtraInfo);	//���ӵĶ�����Ϣ

	//ÿ����Ϸѭ���������
	//������Щ��ʱ���͵���Ϣ
	void DispatchDelayedMessages();
};