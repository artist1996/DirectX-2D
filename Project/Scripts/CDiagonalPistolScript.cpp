#include "pch.h"
#include "CDiagonalPistolScript.h"
#include "CDirezieScript.h"

CDiagonalPistolScript::CDiagonalPistolScript()
	: CScript(SCRIPT_TYPE::DIAGONALPISTOLSCRIPT)
	, m_Speed(700.f)
	, m_DestroyPos(0.f)
{
}

CDiagonalPistolScript::~CDiagonalPistolScript()
{
}

void CDiagonalPistolScript::Begin()
{
	Animator2D()->Play(0, 10.f, true);

	if (OBJ_DIR::DIR_LEFT == GetOwner()->GetParent()->GetDir())
	{
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI / 3.3f));
	}

	else if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetParent()->GetDir())
	{
		Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
	}
}

void CDiagonalPistolScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vParentPos = GetOwner()->GetParent()->Transform()->GetRelativePos();

	switch (GetOwner()->GetParent()->GetDir())
	{
	case OBJ_DIR::DIR_LEFT:
		vParentPos += Vec3(-1.f, 0.f, 0.f) * 1000.f * DT;
		vPos.y -= 500.f * DT;
		break;
	case OBJ_DIR::DIR_RIGHT:
		vParentPos += Vec3(1.f, 0.f, 0.f) * 1000.f * DT;
		vPos.y -= 500.f * DT;
		break;
	}

	if (vPos.y < 0.f)
		DeleteObject(GetOwner()->GetParent());

	Transform()->SetRelativePos(vPos);
	GetOwner()->GetParent()->Transform()->SetRelativePos(vParentPos);
}

void CDiagonalPistolScript::SaveToFile(FILE* _pFile)
{
}

void CDiagonalPistolScript::LoadFromFile(FILE* _pFile)
{
}

void CDiagonalPistolScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDiagonalPistolScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		if (GetOwner()->GetParent()->GetGroundCollision())
		{
			INFO& info = _OtherObj->GetInfo();
			info.HP -= 10.f;
			DeleteObject(GetOwner()->GetParent());
		}
	}
}

void CDiagonalPistolScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}