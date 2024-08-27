#include "pch.h"
#include "CDoubleGunHawkScript.h"
#include <Engine/CLevelMgr.h>

#include "CPlayerScript.h"


CDoubleGunHawkScript::CDoubleGunHawkScript()
	: CScript(SCRIPT_TYPE::DOUBLEGUNHAWKSCRIPT)
	, m_Type(GUNHAWK_TYPE::END)
	, m_Time(0.f)
	, m_StopTime(1.f)
	, m_Move(true)
	, m_ReverseMove(false)
	, m_Stop(false)
{
	AddScriptParam(SCRIPT_PARAM::VEC3, "DIRECTION", &m_Dir);
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_Type);
}

CDoubleGunHawkScript::~CDoubleGunHawkScript()
{
}

void CDoubleGunHawkScript::Begin()
{
	Animator2D()->Play(0, 30.f, true);
}

void CDoubleGunHawkScript::Tick()
{
	Vec3 InitPos = GetOwner()->GetInitPos();
	Vec3 vPos = Transform()->GetRelativePos();
	
	if (m_Move)
	{
		if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		{
			vPos.x += -m_Dir.x * 700.f * DT;
			vPos.y += m_Dir.y * 40.f * DT;
		}
			
		else if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetDir())
		{
			vPos.x += m_Dir.x * 700.f * DT;
			vPos.y += m_Dir.y * 40.f * DT;
		}

		if (300.f < fabs(vPos.x - InitPos.x))
		{
			m_Move = false;
			m_Stop = true;
		}
	}

	else if (m_Stop)
	{
		m_Time += DT;

		if (1.f < m_Time)
		{
			m_Stop = false;
			m_ReverseMove = true;
		}
	}

	else if (m_ReverseMove)
	{
		if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		{
			vPos.x +=  m_Dir.x * 800.f * DT;
			vPos.y += -m_Dir.y * 30.f * DT;

		}

		else if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetDir())
		{
			vPos.x += -m_Dir.x * 800.f * DT;
			vPos.y += -m_Dir.y * 30.f * DT;
		}
	
		if (1200.f < fabs(InitPos.x - vPos.x))
		{
			m_Move = false;
			m_Stop = true;

			DeleteObject(GetOwner());
		}
	}

	Transform()->SetRelativePos(vPos);
}

void CDoubleGunHawkScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDoubleGunHawkScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDoubleGunHawkScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (GUNHAWK_TYPE::TYPE_ONE == m_Type && m_ReverseMove)
	{
		CPlayerScript* pScript = (CPlayerScript*)CLevelMgr::GetInst()->FindObjectByName(L"Player")->FindScriptByName(L"CPlayerScript");

		pScript->ChangeStateDoubleGunHawkStandBy();

		DeleteObject(GetOwner());
	}
}

void CDoubleGunHawkScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Type, sizeof(GUNHAWK_TYPE), 1, _pFile);
	fwrite(&m_Dir, sizeof(Vec3), 1, _pFile);
	fwrite(&m_StopTime, sizeof(float), 1, _pFile);
}

void CDoubleGunHawkScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Type, sizeof(GUNHAWK_TYPE), 1, _pFile);
	fread(&m_Dir, sizeof(Vec3), 1, _pFile);
	fread(&m_StopTime, sizeof(float), 1, _pFile);
}
