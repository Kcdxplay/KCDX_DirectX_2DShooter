#pragma once

#include "BasePart.h"
#include "Charcter.h"
#include "AState.h"

template <typename type>
class AStateMachine
{
private:
	type* pOwner;
	AState<type>* pPreviousState;	//֮ǰ��״̬ �����Զ��ص�֮ǰ״̬
	AState<type>* pCurrentState;	//��ǰ״̬
	AState<type>* pGlobalState;		//ȫ��״̬

public:
	AStateMachine() {}
	AStateMachine(type* owner) :pOwner(owner), pCurrentState(NULL), pGlobalState(NULL) {}

	//���ڳ�ʼ���ķ���
	void SetCurrentState(AState<type>* s) { pCurrentState = s; }
	void SetGlobalState(AState<type>* s) { pGlobalState = s; }
	void SetPreviousState(AState<type>* s) { pPreviousState = s; }

	//����FSM
	void Update()
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
	void ChangeState(AState<type>* pNewState)
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

	AState<type>* GetCurrentState()
	{
		return pCurrentState;
	}
	AState<type>* GetGlobalState()
	{
		return pGlobalState;
	}
	AState<type>* GetPreviousState()
	{
		return pPreviousState;
	}
};