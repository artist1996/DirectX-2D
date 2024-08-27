#include "pch.h"
#include "CDoubleGunHawkScript.h"
#include <Engine/CLevelMgr.h>

#include "CPlayerScript.h"


CDoubleGunHawkScript::CDoubleGunHawkScript()
	: CScript(SCRIPT_TYPE::DOUBLEGUNHAWKSCRIPT)
	, m_Type(GUNHAWK_TYPE::END)
	, m_Time(0.f)
	, m_StopTime(1.f)
	, m_Force(600.f)
	, m_Accel(0.f)
	, m_Friction(500.f)
	, m_Mass(1.f)
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

	MeshRender()->GetMaterial()->SetScalarParam(INT_3, 1);

	m_Accel = m_Force / m_Mass;
}

void CDoubleGunHawkScript::Tick()
{
	Vec3 InitPos = GetOwner()->GetInitPos();
	Vec3 vPos = Transform()->GetRelativePos();
	
	if (m_Move)
	{
		//m_Accel = (m_Force * 1.2f) / m_Mass;

		if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		{
			vPos.x += -m_Dir.x * m_Accel * 1.25f * DT;
			vPos.y += m_Dir.y * m_Accel / 14.f * DT;
		}

		else if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetDir())
		{
			vPos.x += m_Dir.x * m_Accel * 1.25f * DT;
			vPos.y += m_Dir.y * m_Accel / 14.f * DT;
		}

		if (250.f < fabs(vPos.x - InitPos.x))
		{
			m_Move = false;
			m_ReverseMove = true;
		}
		m_Accel -= m_Friction * DT;
	}

	else if (m_Stop)
	{
		m_Time += DT;

		if (0.1f < m_Time)
		{
			m_Stop = false;
			m_ReverseMove = true;
		}
	}

	else if (m_ReverseMove)
	{
		//m_Accel = (m_Force * 1.5f) / m_Mass;

		if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		{
			vPos.x -=  m_Dir.x * m_Accel * 1.5f * DT;
			vPos.y += m_Dir.y * m_Accel / 6.f * DT;
		}

		else if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetDir())
		{
			vPos.x -= -m_Dir.x * m_Accel * 1.5f * DT;
			vPos.y += m_Dir.y * m_Accel / 6.f * DT;
		}
	
		if (1200.f < fabs(InitPos.x - vPos.x))
		{
			m_Move = false;
			m_Stop = true;

			DeleteObject(GetOwner());
		}

		m_Accel -= m_Friction * DT;
	}

	Transform()->SetRelativePos(vPos);
}

void CDoubleGunHawkScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		if (GUNHAWK_TYPE::TYPE_ONE == m_Type && m_ReverseMove)
		{
			CPlayerScript* pScript = (CPlayerScript*)CLevelMgr::GetInst()->FindObjectByName(L"Player")->FindScriptByName(L"CPlayerScript");

			pScript->ChangeStateDoubleGunHawkStandBy();

			DeleteObject(GetOwner());
			_OtherCollider->MinusOverlapCount();
		}
	}
}

void CDoubleGunHawkScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDoubleGunHawkScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
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
