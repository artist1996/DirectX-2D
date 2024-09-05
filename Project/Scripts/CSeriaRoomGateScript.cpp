#include "pch.h"
#include "CSeriaRoomGateScript.h"

#include <Engine/CObjectPoolMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CSeriaRoomGateScript::CSeriaRoomGateScript()
	: CScript(SCRIPT_TYPE::SERIAROOMGATESCRIPT)
{
}

CSeriaRoomGateScript::~CSeriaRoomGateScript()
{
}

void CSeriaRoomGateScript::Begin()
{
}

void CSeriaRoomGateScript::Tick()
{
}

void CSeriaRoomGateScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"PlayerMove" == _OtherObj->GetName())
	{
		CGameObject* pPlayer = CObjectPoolMgr::GetInst()->GetPlayerEntity();

		DisconnectObject(pPlayer);

		ChangeCurLevel(LEVEL_TYPE::HENDONMYER);

		//_OtherObj->Transform()->SetRelativePos(-82.f, 24.f, 0.f);
		pPlayer->Transform()->SetRelativePos(-82.f, 24.f, 0.f);
		CreateObject(pPlayer, 4);
		
		//ChangeLevelState(PLAY);
	}
}