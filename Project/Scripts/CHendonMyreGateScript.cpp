#include "pch.h"
#include "CHendonMyreGateScript.h"

#include <Engine/CObjectPoolMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CHendonMyreGateScript::CHendonMyreGateScript()
	: CScript(SCRIPT_TYPE::HENDONMYREGATESCRIPT)
{
}

CHendonMyreGateScript::~CHendonMyreGateScript()
{
}

void CHendonMyreGateScript::Begin()
{
}

void CHendonMyreGateScript::Tick()
{
}

void CHendonMyreGateScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"PlayerMove" == _OtherObj->GetName())
	{
		CGameObject* pPlayer = CObjectPoolMgr::GetInst()->GetPlayerEntity();

		DisconnectObject(pPlayer);

		ChangeCurLevel(LEVEL_TYPE::LESHPHON1);

		pPlayer->Transform()->SetRelativePos(650.f, 0.f, 0.f);
		CreateObject(pPlayer, 4);

		ChangeLevelState(PLAY);
	}
}