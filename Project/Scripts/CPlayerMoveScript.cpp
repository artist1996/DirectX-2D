#include "pch.h"
#include "CPlayerMoveScript.h"

#include <Engine/CTransform.h>
#include <Engine/CAnimator2D.h>

CPlayerMoveScript::CPlayerMoveScript()
	: CScript(SCRIPT_TYPE::PLAYERMOVESCRIPT)
	, m_State(STATE::ST_IDLE)
	, m_Speed(300.f)
	, m_MoveAble(true)
	, m_TapMove(false)
{
}

CPlayerMoveScript::~CPlayerMoveScript()
{
}

void CPlayerMoveScript::Begin()
{
}

void CPlayerMoveScript::Tick()
{
	switch (m_State)
	{
	case CPlayerMoveScript::ST_IDLE:
		Idle();
		break;
	case CPlayerMoveScript::ST_MOVE:
		Move();
		break;
	case CPlayerMoveScript::ST_RUN:
		Run();
		break;
	}
}

void CPlayerMoveScript::Idle()
{
	if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT))
	{
		m_State = ST_MOVE;
	}
	if (KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
	{
		m_State = ST_MOVE;
	}
	if (KEY_TAP(KEY::UP) || KEY_PRESSED(KEY::UP))
	{
		m_State = ST_MOVE;
	}
	if (KEY_TAP(KEY::DOWN) || KEY_PRESSED(KEY::DOWN))
	{
		m_State = ST_MOVE;
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