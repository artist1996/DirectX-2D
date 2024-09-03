#include "pch.h"
#include "CStateMgr.h"

#include "CMeltKnightIdleState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CMeltKnightIdleState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CMeltKnightIdleState" == _strStateName)
		return new CMeltKnightIdleState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::MELTKNIGHTIDLESTATE:
		return new CMeltKnightIdleState;
		break;
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::MELTKNIGHTIDLESTATE:
		return L"CMeltKnightIdleState";
		break;

	}
	return nullptr;
}