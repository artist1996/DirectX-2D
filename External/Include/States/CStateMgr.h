#pragma once

#include <vector>
#include <string>

enum STATE_TYPE
{
	HYUNGTEOBUFFEATERSTATE,
	HYUNGTEODEADSTATE,
	HYUNGTEOEATSTATE,
	HYUNGTEOFALLSTATE,
	HYUNGTEOFLYSTATE,
	HYUNGTEOHITSTATE,
	HYUNGTEOIDLESTATE,
	HYUNGTEOLOOKSTATE,
	HYUNGTEOPUNCHSTATE,
	HYUNGTEOSTINGSTATE,
	HYUNGTEOTRACESTATE,
	HYUNGTEOWAKEUPSTATE,
	MELTKNIGHTATTACKSTATE,
	MELTKNIGHTDEADSTATE,
	MELTKNIGHTIDLESTATE,
	MELTKNIGHTSTANDBYSTATE,
	MELTKNIGHTTRACESTATE,
};

using namespace std;

class CState;

class CStateMgr
{
public:
	static void GetStateInfo(vector<wstring>& _vec);
	static CState * GetState(const wstring& _strStateName);
	static CState * GetState(UINT _iStateType);
	static const wchar_t * GetStateName(CState * _pState);
};
