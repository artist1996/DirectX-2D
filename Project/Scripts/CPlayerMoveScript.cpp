#include "pch.h"
#include "CPlayerMoveScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CObjectPoolMgr.h>
#include <Engine/CFontMgr.h>

#include <Engine/CTransform.h>
#include <Engine/CAnimator2D.h>


#include "CPlayerScript.h"

CPlayerMoveScript::CPlayerMoveScript()
	: CScript(SCRIPT_TYPE::PLAYERMOVESCRIPT)
	, m_Speed(350.f)
{
}

CPlayerMoveScript::~CPlayerMoveScript()
{
}

void CPlayerMoveScript::AddForce()
{
	OBJ_DIR Dir = GetOwner()->GetDir();

	if (OBJ_DIR::DIR_RIGHT == Dir)
		Rigidbody()->AddForce(Vec3(-70000.f, 0.f, 0.f));
	else if (OBJ_DIR::DIR_LEFT == Dir)
		Rigidbody()->AddForce(Vec3(70000.f, 0.f, 0.f));
}

void CPlayerMoveScript::Begin()
{
	GetOwner()->SetID(OBJ_ID::PLAYER);
	INFO& info = GetOwner()->GetInfo();
	info.bMoveable = true;
	info.bTackle = false;
}

void CPlayerMoveScript::Tick()
{
	INFO& info = GetOwner()->GetInfo();

	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();
	bool* bMoveable = GetOwner()->GetMoveable();
	
	if (info.bMoveable)
	{
		if (KEY_PRESSED(KEY::RIGHT) && bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
		{
			vPos += Vec3(1.f, 0.f, 0.f) * info.Speed * DT;
			vRot = Vec3(0.f, XM_PI, 0.f);
			GetOwner()->SetDir(OBJ_DIR::DIR_RIGHT);
		}
		if (KEY_PRESSED(KEY::LEFT) && bMoveable[(UINT)PLATFORM_TYPE::LEFT])
		{
			vPos += Vec3(-1.f, 0.f, 0.f) * info.Speed * DT;
			vRot = Vec3(0.f, 0.f, 0.f);
			GetOwner()->SetDir(OBJ_DIR::DIR_LEFT);
		}
		if (KEY_PRESSED(KEY::UP) && bMoveable[(UINT)PLATFORM_TYPE::UP])
			vPos += Vec3(0.f, 1.f, 0.f) * m_Speed * DT;
		if (KEY_PRESSED(KEY::DOWN) && bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
			vPos += Vec3(0.f, -1.f, 0.f) * m_Speed * DT;
	}

	if (info.bTackle)
	{
		OBJ_DIR Dir = GetOwner()->GetDir();

		if (OBJ_DIR::DIR_LEFT == Dir && bMoveable[(UINT)PLATFORM_TYPE::LEFT])
		{
			vPos += Vec3(-1.f, 0.f, 0.f) * 1500.f * DT;
		}
		else if (OBJ_DIR::DIR_RIGHT == Dir && bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
		{
			vPos += Vec3(1.f, 0.f, 0.f) * 1500.f * DT;
		}
	}

	if (info.bForce)
	{
		AddForce();
		info.bForce = false;
	}


	Transform()->SetRelativePos(Vec3(vPos.x, vPos.y, vPos.y));
	Transform()->SetRelativeRotation(vRot);
}

void CPlayerMoveScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerMoveScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerMoveScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerMoveScript::SaveToFile(FILE* _pFile)
{
}

void CPlayerMoveScript::LoadFromFile(FILE* _pFile)
{
}