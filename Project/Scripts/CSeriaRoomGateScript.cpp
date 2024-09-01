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
		CGameObject* pMove = CObjectPoolMgr::GetInst()->GetPlayerMove();
		CGameObject* pPlayer = CObjectPoolMgr::GetInst()->GetPlayerEntity();
		CGameObject* pJump = CObjectPoolMgr::GetInst()->GetPlayerJump();
		DisconnectObject(pMove);
		DisconnectObject(pPlayer);
		DisconnectObject(pJump);

		ChangeCurLevel(LEVEL_TYPE::HENDONMYER);

		_OtherObj->Transform()->SetRelativePos(-50.f, 0.f, 0.f);
		pPlayer->Transform()->SetRelativePos(pMove->Transform()->GetWorldPos());
		CreateObject(pMove, 5);
		CreateObject(pPlayer, 4);
		CreateObject(pJump, 4);
		
		ChangeLevelState(PLAY);
	}
}