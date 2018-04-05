#pragma once

struct Telegram;
class CharcterDetailData;
class Graphic;

template <typename type>
class MState	//MotionState�˶�״̬
{
public:
	CharcterDetailData* pData;
	Graphic* pGraph;

	virtual void Enter(type*) = 0;		//����״̬�Ĳ���
	virtual void Execute(type*) = 0;	//ִ��״̬�������
	virtual void Exit(type*) = 0;		//�˳�״̬�Ĳ���

	//����յ��˷��������͵���Ϣ�����������������
	virtual bool OnMessage(type*, const Telegram&) = 0;

	virtual ~MState() {}
};