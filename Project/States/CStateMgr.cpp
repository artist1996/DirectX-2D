#include "pch.h"
#include "CStateMgr.h"

#include "CMeltKnightAttackState.h"
#include "CMeltKnightDeadState.h"
#include "CMeltKnightIdleState.h"
#include "CMeltKnightStandByState.h"
#include "CMeltKnightTraceState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CMeltKnightAttackState");
	_vec.push_back(L"CMeltKnightDeadState");
	_vec.push_back(L"CMeltKnightIdleState");
	_vec.push_back(L"CMeltKnightStandByState");
	_vec.push_back(L"CMeltKnightTraceState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CMeltKnightAttackState" == _strStateName)
		return new CMeltKnightAttackState;
	if (L"CMeltKnightDeadState" == _strStateName)
		return new CMeltKnightDeadState;
	if (L"CMeltKnightIdleState" == _strStateName)
		return new CMeltKnightIdleState;
	if (L"CMeltKnightStandByState" == _strStateName)
		return new CMeltKnightStandByState;
	if (L"CMeltKnightTraceState" == _strStateName)
		return new CMeltKnightTraceState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::MELTKNIGHTATTACKSTATE:
		return new CMeltKnightAttackState;
		break;
	case (UINT)STATE_TYPE::MELTKNIGHTDEADSTATE:
		return new CMeltKnightDeadState;
		break;
	case (UINT)STATE_TYPE::MELTKNIGHTIDLESTATE:
		return new CMeltKnightIdleState;
		break;
	case (UINT)STATE_TYPE::MELTKNIGHTSTANDBYSTATE:
		return new CMeltKnightStandByState;
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
	case STATE_TYPE::MELTKNIGHTATTACKSTATE:
		return L"CMeltKnightAttackState";
		break;

	case STATE_TYPE::MELTKNIGHTDEADSTATE:
		return L"CMeltKnightDeadState";
		break;

	case STATE_TYPE::MELTKNIGHTIDLESTATE:
		return L"CMeltKnightIdleState";
		break;

	case STATE_TYPE::MELTKNIGHTSTANDBYSTATE:
		return L"CMeltKnightStandByState";
		break;

	case STATE_TYPE::MELTKNIGHTTRACESTATE:
		return L"CMeltKnightTraceState";
		break;

	}
	return nullptr;
}