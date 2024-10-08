#include "pch.h"
#include "LeshphonGateScript.h"
#include <Engine/CObjectPoolMgr.h>

#include <Engine/CLevelMgr.h>

LeshphonGateScript::LeshphonGateScript()
	: CScript(SCRIPT_TYPE::ESHPHONGATESCRIPT)
	, m_Type(GATE_TYPE::END)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_Type);
}

LeshphonGateScript::~LeshphonGateScript()
{
}

void LeshphonGateScript::Begin()
{
}

void LeshphonGateScript::Tick()
{
}

void LeshphonGateScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"PlayerMove" == _OtherObj->GetName())
	{
		CGameObject* pPlayer = CObjectPoolMgr::GetInst()->GetPlayerEntity();
		switch (m_Type)
		{
		case GATE_TYPE::LESHPHON1:
		{
			DisconnectObject(pPlayer);
			
			ChangeCurLevel(LEVEL_TYPE::LESHPHON2);
			
			pPlayer->Transform()->SetRelativePos(Vec3(650.f, -50.f, 0.f));
			CreateObject(pPlayer, 4);
			ChangeLevelState(LEVEL_STATE::PLAY);
		}
			break;
		case GATE_TYPE::LESHPHON2:
		{
			DisconnectObject(pPlayer);
			ChangeCurLevel(LEVEL_TYPE::LESHPHON3);
			pPlayer->Transform()->SetRelativePos(Vec3(650.f, -50.f, 0.f));
			CreateObject(pPlayer, 4);
			ChangeLevelState(LEVEL_STATE::PLAY);
		}
			break;
		case GATE_TYPE::LESHPHON3:
		{
			DisconnectObject(pPlayer);
			ChangeCurLevel(LEVEL_TYPE::LESHPHON4);
			pPlayer->Transform()->SetRelativePos(Vec3(600.f, -50.f, 0.f));
			CreateObject(pPlayer, 4);
			ChangeLevelState(LEVEL_STATE::PLAY);
		}
			break;
		}
	}
}

void LeshphonGateScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Type, sizeof(GATE_TYPE), 1, _pFile);
}

void LeshphonGateScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Type, sizeof(GATE_TYPE), 1, _pFile);
}