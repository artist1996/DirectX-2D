#include "pch.h"
#include "CStateMgr.h"

#include "CMeltKnightIdleState.h"
#include "CMeltKnightTraceState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CMeltKnightIdleState");
	_vec.push_back(L"CMeltKnightTraceState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CMeltKnightIdleState" == _strStateName)
		return new CMeltKnightIdleState;
	if (L"CMeltKnightTraceState" == _strStateName)
		return new CMeltKnightTraceState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::MELTKNIGHTIDLESTATE:
		return new CMeltKnightIdleState;
		break;
	case (UINT)STATE_TYPE::MELTKNIGHTTRACESTATE:
		return new CMeltKnightTraceState;
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

	case STATE_TYPE::MELTKNIGHTTRACESTATE:
		return L"CMeltKnightTraceState";
		break;

	}
	return nullptr;
}