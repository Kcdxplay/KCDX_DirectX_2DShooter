#pragma once

#include "BasePart.h"
#include "Charcter.h"

template <typename type>
class MStateMachine
{
private:
	type* pOwner;
	MState<type>* pPreviousState;	//֮ǰ��״̬ �����Զ��ص�֮ǰ״̬
	MState<type>* pCurrentState;	//��ǰ״̬
	MState<type>* pGlobalState;		//ȫ��״̬

public:
	MStateMachine() {}
	MStateMachine(type* owner) :pOwner(owner), pCurrentState(NULL), pGlobalState(NULL) {}

	//���ڳ�ʼ���ķ���
	void SetCurrentState(MState<type>* s) { pCurrentState = s; }
	void SetGlobalState(MState<type>* s) { pGlobalState = s; }
	void SetPreviousState(MState<type>* s) { pPreviousState = s; }

	//����FSM
	void Update()const
	{
		//ִ��ȫ��״̬
		if (pGlobalState) { pGlobalState->Execute(pOwner); }

		//ִ�е�ǰ״̬
		if (pCurrentState) { pCurrentState->Execute(pOwner); }
	}

	bool HandleMessage(const Telegram& msg)
	{
		if (pCurrentState&&pCurrentState->OnMessage(pOwner, msg))
		{
			return true;
		}

		if (pGlobalState&&pGlobalState->OnMessage(pOwner, msg))
		{
			return true;
		}

		return false;
	}

	//���״̬
	void ChangeState(MState<type>* pNewState)
	{
		pPreviousState = pCurrentState;

		pCurrentState->Exit(pOwner);
		pCurrentState = pNewState;
		pCurrentState->Enter(pOwner);
	}
	void RevertToPreviousState()
	{
		ChangeState(pPreviousState);
	}

	MState<type>* GetCurrentState()
	{
		return pCurrentState;
	}
	MState<type>* GetGlobalState()
	{
		return pGlobalState;
	}
	MState<type>* GetPreviousState()
	{
		return pPreviousState;
	}
};

