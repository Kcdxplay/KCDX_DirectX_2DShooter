#pragma once

#include "BasePart.h"
#include "Charcter.h"
#include "AState.h"

template <typename type>
class AStateMachine
{
private:
	type* pOwner;
	AState<type>* pPreviousState;	//之前的状态 用于自动回到之前状态
	AState<type>* pCurrentState;	//当前状态
	AState<type>* pGlobalState;		//全局状态

public:
	AStateMachine() {}
	AStateMachine(type* owner) :pOwner(owner), pCurrentState(NULL), pGlobalState(NULL) {}

	//用于初始化的方法
	void SetCurrentState(AState<type>* s) { pCurrentState = s; }
	void SetGlobalState(AState<type>* s) { pGlobalState = s; }
	void SetPreviousState(AState<type>* s) { pPreviousState = s; }

	//更新FSM
	void Update()
	{
		//执行全局状态
		if (pGlobalState) { pGlobalState->Execute(pOwner); }

		//执行当前状态
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

	//变更状态
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