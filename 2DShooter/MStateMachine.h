#pragma once

#include "BasePart.h"
#include "Charcter.h"

template <typename type>
class MStateMachine
{
private:
	type* pOwner;
	MState<type>* pPreviousState;	//之前的状态 用于自动回到之前状态
	MState<type>* pCurrentState;	//当前状态
	MState<type>* pGlobalState;		//全局状态

public:
	MStateMachine() {}
	MStateMachine(type* owner) :pOwner(owner), pCurrentState(NULL), pGlobalState(NULL) {}

	//用于初始化的方法
	void SetCurrentState(MState<type>* s) { pCurrentState = s; }
	void SetGlobalState(MState<type>* s) { pGlobalState = s; }
	void SetPreviousState(MState<type>* s) { pPreviousState = s; }

	//更新FSM
	void Update()const
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

