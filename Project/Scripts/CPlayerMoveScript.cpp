#include "pch.h"
#include "CPlayerMoveScript.h"

#include <Engine/CLevelMgr.h>

#include <Engine/CTransform.h>
#include <Engine/CAnimator2D.h>

#include "CPlayerScript.h"
#include "CPlayerJumpScript.h"

CPlayerMoveScript::CPlayerMoveScript()
	: CScript(SCRIPT_TYPE::PLAYERMOVESCRIPT)
	, m_EntityScript(nullptr)
	, m_JumpScript(nullptr)
	, m_State(MOVE_STATE::ST_IDLE)
	, m_Speed(300.f)
	, m_MoveAble(true)
	, m_TapMove(false)
	, m_ForceTime(0.f)
{
	SetName(L"CPlayerMoveScript");
}

CPlayerMoveScript::~CPlayerMoveScript()
{
}

void CPlayerMoveScript::Begin()
{
	CGameObject* pObject = CLevelMgr::GetInst()->FindObjectByName(L"PlayerJump");
	m_JumpScript = (CPlayerJumpScript*)pObject->FindScriptByName(L"CPlayerJumpScript");

	pObject = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	m_EntityScript = (CPlayerScript*)pObject->FindScriptByName(L"CPlayerScript");

	Collider2D()->SetOffset(Vec3(0.15f, -4.f, 0.f));
}

void CPlayerMoveScript::Tick()
{
	switch (m_State)
	{
	case ST_IDLE:
		Idle();
		break;
	case ST_MOVE:
		Move();
		break;
	case ST_RUN:
		Run();
		break;
	case ST_TACKLE:
		Tackle();
		break;
	case ST_FORCE:
		Force();
		break;
	}
}

void CPlayerMoveScript::Idle()
{
	if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT))
	{
		m_State = ST_MOVE;
		Collider2D()->SetOffset(Vec3(-0.1f, -4.f, 0.f));

		CorrectionSpeed();
	}
	if (KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
	{
		m_State = ST_MOVE;
		Collider2D()->SetOffset(Vec3(0.15f, -4.f, 0.f));

		CorrectionSpeed();
	}
	if (KEY_TAP(KEY::UP) || KEY_PRESSED(KEY::UP))
	{
		m_State = ST_MOVE;
		CorrectionSpeed();
	}
	if (KEY_TAP(KEY::DOWN) || KEY_PRESSED(KEY::DOWN))
	{
		m_State = ST_MOVE;
		CorrectionSpeed();
	}

	//m_TapMove = true;
	

	//else
	//{
	//	if (KEY_TAP(KEY::LEFT))
	//	{
	//		m_State = ST_RUN;
	//	}
	//	if (KEY_TAP(KEY::RIGHT))
	//	{
	//		m_State = ST_RUN;
	//	}
	//	if (KEY_TAP(KEY::UP))
	//	{
	//		m_State = ST_RUN;
	//	}
	//	if (KEY_TAP(KEY::DOWN))
	//	{
	//		m_State = ST_RUN;
	//	}
	//
	//	m_TapMove = false;
	//}
}

void CPlayerMoveScript::Move()
{
	Vec3 vPos = Transform()->GetRelativePos();
	bool* bMoveable = GetOwner()->GetMoveable();

	if (m_MoveAble)
	{
		if (KEY_PRESSED(KEY::LEFT) && bMoveable[(UINT)PLATFORM_TYPE::LEFT])
			vPos += Vec3(-1.f, 0.f, 0.f) * m_Speed * DT;
		else if (KEY_RELEASED(KEY::LEFT))
			m_State = ST_IDLE;
		if (KEY_PRESSED(KEY::RIGHT) && bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
			vPos += Vec3(1.f, 0.f, 0.f) * m_Speed * DT;
		else if (KEY_RELEASED(KEY::RIGHT))
			m_State = ST_IDLE;
		if (KEY_PRESSED(KEY::UP) && bMoveable[(UINT)PLATFORM_TYPE::UP])
			vPos += Vec3(0.f, 1.f, 1.f) * m_Speed * DT;
		else if (KEY_RELEASED(KEY::UP))
			m_State = ST_IDLE;
		if (KEY_PRESSED(KEY::DOWN) && bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
			vPos += Vec3(0.f, -1.f, -1.f) * m_Speed * DT;
		else if (KEY_RELEASED(KEY::DOWN))
			m_State = ST_IDLE;

		Transform()->SetRelativePos(vPos);
	}
}

void CPlayerMoveScript::Run()
{
	//Vec3 vPos = Transform()->GetRelativePos();
	//
	//if (m_MoveAble)
	//{
	//	if (KEY_PRESSED(KEY::LEFT))
	//		vPos += Vec3(-1.f, 0.f, 0.f) * m_Speed * 1.5f * DT;
	//	else if (KEY_RELEASED(KEY::LEFT))
	//		m_State = ST_IDLE;
	//	if (KEY_PRESSED(KEY::RIGHT))
	//		vPos += Vec3(1.f, 0.f, 0.f) * m_Speed * 1.5f * DT;
	//	else if (KEY_RELEASED(KEY::RIGHT))
	//		m_State = ST_IDLE;
	//	if (KEY_PRESSED(KEY::UP))
	//		vPos += Vec3(1.f, 0.f, 1.f) * m_Speed * 1.5f * DT;
	//	else if (KEY_RELEASED(KEY::UP))
	//		m_State = ST_IDLE;
	//	if (KEY_PRESSED(KEY::DOWN))
	//		vPos += Vec3(-1.f, 0.f, -1.f) * m_Speed * 1.5f * DT;
	//	else if (KEY_RELEASED(KEY::DOWN))
	//		m_State = ST_IDLE;
	//
	//	Transform()->SetRelativePos(vPos);
	//}
}

void CPlayerMoveScript::Tackle()
{
	Vec3 vPos = Transform()->GetRelativePos();
	bool* bMoveable = GetOwner()->GetMoveable();

	if (OBJ_DIR::DIR_RIGHT == m_EntityScript->GetDir()
		&& bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vPos += Vec3(1.f, 0.f, 0.f) * m_Speed * 2.5f * DT;
	}

	else if (OBJ_DIR::DIR_LEFT == m_EntityScript->GetDir()
		&& bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		vPos += Vec3(-1.f, 0.f, 0.f) * m_Speed * 2.5f * DT;
	}

	Transform()->SetRelativePos(vPos);
}

void CPlayerMoveScript::Force()
{
	m_ForceTime += DT;

	if(OBJ_DIR::DIR_LEFT == m_EntityScript->GetDir())
		Rigidbody()->AddForce(Vec3(1000.f, 0.f, 0.f));
	else if(OBJ_DIR::DIR_RIGHT == m_EntityScript->GetDir())
		Rigidbody()->AddForce(Vec3(-1000.f, 0.f, 0.f));

	if (0.1f < m_ForceTime)
	{
		SetState(MOVE_STATE::ST_IDLE);
		m_ForceTime = 0.f;
	}
}

void CPlayerMoveScript::CorrectionSpeed()
{
	if (m_JumpScript->IsNormalJump())
		m_Speed = 50.f;
	else
		m_Speed = 300.f;
}

void CPlayerMoveScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (5 == _OtherObj->GetLayerIdx())
	{
		m_MoveAble = false;
	}
}

void CPlayerMoveScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (5 == _OtherObj->GetLayerIdx())
	{
		m_MoveAble = true;
	}
}

void CPlayerMoveScript::SaveToFile(FILE* _pFile)
{
}

void CPlayerMoveScript::LoadFromFile(FILE* _pFile)
{
}