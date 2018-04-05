#pragma once
#include "DirectX.h"

struct Telegram;

class BaseGameEntity
{
private:
	int mID;	//��Ϸ���ӦID
	static int mNextID;	//��һ����ЧID

	void SetID(int val);

public:
	BaseGameEntity(){}
	BaseGameEntity(int id)
	{
		SetID(id);
	}

	//��ش�����
	virtual void Update() = 0;
	virtual void Render() = 0;

	//��Ϣ���ջ���
	virtual bool HandleMessage(const Telegram& msg) = 0;

	int ID() const { return mID; }
};

class Graphic	//ͼ��ģ��
{
public:
	LPDIRECT3DTEXTURE9 texture;	//��ͼ
	
	D3DXVECTOR3 paintPos;		//��Ļ����λ��
	D3DXVECTOR2 mapPos;			//��ͼ���λ��
	D3DXVECTOR2 scale;			//����
	D3DXVECTOR2 center;			//��������
	D3DXVECTOR2 trans;			//X��Y��λ��
	double rotation;			//��ת�Ƕ�
	//D3DXVECTOR2 direction;	//����
	D3DXMATRIX TransMat;		//���ű�����
	bool towards;				//���Ƴ���	False-����  True-����

	//----------�������
	int frameW;					//ÿ֡���
	int frameH;					//ÿ֡�߶�
	int frameNum;				//�����ǵڼ�֡
	int startframe;				//�ӵڼ�֡��ʼ
	int endframe;				//���ڼ�֡����
	int columns;				//���������
	int delay;					//����ÿ֡��ʱ

	int lastTime = GetTickCount();	//�ϴλ���ʱ��

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


//���ڳ�ʼ��һ����Ϸ��ɫ
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
//�Ż��ӵ���ײ�жϣ��洢��ײ�����Ϣ
struct RectCollision
{
	RECT mainRect;			//��������
	D3DXVECTOR2 collisionPoint;	//��ײ����
	RC_DetailInfo extraInfo;//������Ϣ
};

enum RectType
{
	WallRect,
	EnemyRect
};

////��Ϣ�ṹ��
//struct Telegram
//{
//	//������ʵ��
//	int Sender;
//	//������ʵ��
//	int Receiver;
//	//��Ϣ����
//	int Msg;
//	
//	//��ʱʱ��
//	double DispatchTime;
//	//���ܻ��еĶ�����Ϣ
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