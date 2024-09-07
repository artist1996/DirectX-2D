#include "pch.h"
#include "CStateMgr.h"

#include "CHyungteoBuffEaterState.h"
#include "CHyungteoDeadState.h"
#include "CHyungteoEatState.h"
#include "CHyungteoFallState.h"
#include "CHyungteoFlyState.h"
#include "CHyungteoHitState.h"
#include "CHyungteoIdleState.h"
#include "CHyungteoLookState.h"
#include "CHyungteoPunchState.h"
#include "CHyungteoStingState.h"
#include "CHyungteoTraceState.h"
#include "CHyungteoWakeUpState.h"
#include "CMeltKnightAttackState.h"
#include "CMeltKnightDeadState.h"
#include "CMeltKnightIdleState.h"
#include "CMeltKnightStandByState.h"
#include "CMeltKnightTraceState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CHyungteoBuffEaterState");
	_vec.push_back(L"CHyungteoDeadState");
	_vec.push_back(L"CHyungteoEatState");
	_vec.push_back(L"CHyungteoFallState");
	_vec.push_back(L"CHyungteoFlyState");
	_vec.push_back(L"CHyungteoHitState");
	_vec.push_back(L"CHyungteoIdleState");
	_vec.push_back(L"CHyungteoLookState");
	_vec.push_back(L"CHyungteoPunchState");
	_vec.push_back(L"CHyungteoStingState");
	_vec.push_back(L"CHyungteoTraceState");
	_vec.push_back(L"CHyungteoWakeUpState");
	_vec.push_back(L"CMeltKnightAttackState");
	_vec.push_back(L"CMeltKnightDeadState");
	_vec.push_back(L"CMeltKnightIdleState");
	_vec.push_back(L"CMeltKnightStandByState");
	_vec.push_back(L"CMeltKnightTraceState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CHyungteoBuffEaterState" == _strStateName)
		return new CHyungteoBuffEaterState;
	if (L"CHyungteoDeadState" == _strStateName)
		return new CHyungteoDeadState;
	if (L"CHyungteoEatState" == _strStateName)
		return new CHyungteoEatState;
	if (L"CHyungteoFallState" == _strStateName)
		return new CHyungteoFallState;
	if (L"CHyungteoFlyState" == _strStateName)
		return new CHyungteoFlyState;
	if (L"CHyungteoHitState" == _strStateName)
		return new CHyungteoHitState;
	if (L"CHyungteoIdleState" == _strStateName)
		return new CHyungteoIdleState;
	if (L"CHyungteoLookState" == _strStateName)
		return new CHyungteoLookState;
	if (L"CHyungteoPunchState" == _strStateName)
		return new CHyungteoPunchState;
	if (L"CHyungteoStingState" == _strStateName)
		return new CHyungteoStingState;
	if (L"CHyungteoTraceState" == _strStateName)
		return new CHyungteoTraceState;
	if (L"CHyungteoWakeUpState" == _strStateName)
		return new CHyungteoWakeUpState;
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
	case (UINT)STATE_TYPE::HYUNGTEOBUFFEATERSTATE:
		return new CHyungteoBuffEaterState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEODEADSTATE:
		return new CHyungteoDeadState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEOEATSTATE:
		return new CHyungteoEatState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEOFALLSTATE:
		return new CHyungteoFallState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEOFLYSTATE:
		return new CHyungteoFlyState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEOHITSTATE:
		return new CHyungteoHitState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEOIDLESTATE:
		return new CHyungteoIdleState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEOLOOKSTATE:
		return new CHyungteoLookState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEOPUNCHSTATE:
		return new CHyungteoPunchState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEOSTINGSTATE:
		return new CHyungteoStingState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEOTRACESTATE:
		return new CHyungteoTraceState;
		break;
	case (UINT)STATE_TYPE::HYUNGTEOWAKEUPSTATE:
		return new CHyungteoWakeUpState;
		break;
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
	case STATE_TYPE::HYUNGTEOBUFFEATERSTATE:
		return L"CHyungteoBuffEaterState";
		break;

	case STATE_TYPE::HYUNGTEODEADSTATE:
		return L"CHyungteoDeadState";
		break;

	case STATE_TYPE::HYUNGTEOEATSTATE:
		return L"CHyungteoEatState";
		break;

	case STATE_TYPE::HYUNGTEOFALLSTATE:
		return L"CHyungteoFallState";
		break;

	case STATE_TYPE::HYUNGTEOFLYSTATE:
		return L"CHyungteoFlyState";
		break;

	case STATE_TYPE::HYUNGTEOHITSTATE:
		return L"CHyungteoHitState";
		break;

	case STATE_TYPE::HYUNGTEOIDLESTATE:
		return L"CHyungteoIdleState";
		break;

	case STATE_TYPE::HYUNGTEOLOOKSTATE:
		return L"CHyungteoLookState";
		break;

	case STATE_TYPE::HYUNGTEOPUNCHSTATE:
		return L"CHyungteoPunchState";
		break;

	case STATE_TYPE::HYUNGTEOSTINGSTATE:
		return L"CHyungteoStingState";
		break;

	case STATE_TYPE::HYUNGTEOTRACESTATE:
		return L"CHyungteoTraceState";
		break;

	case STATE_TYPE::HYUNGTEOWAKEUPSTATE:
		return L"CHyungteoWakeUpState";
		break;

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