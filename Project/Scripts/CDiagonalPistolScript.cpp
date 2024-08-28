#include "pch.h"
#include "CDiagonalPistolScript.h"

CDiagonalPistolScript::CDiagonalPistolScript()
	: CScript(SCRIPT_TYPE::DIAGONALPISTOLSCRIPT)
	, m_Speed(700.f)
{
}

CDiagonalPistolScript::~CDiagonalPistolScript()
{
}

void CDiagonalPistolScript::Begin()
{
	Animator2D()->Play(0, 10.f, true);

	if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
	{
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI / 3.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetDir())
	{
		Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
	}

	m_DestroyPos = GetOwner()->GetOwner()->Collider2D()->GetWorldPos();
}

void CDiagonalPistolScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	switch (GetOwner()->GetDir())
	{
	case DIR_LEFT:
		vPos.x -= m_Speed * DT;
		vPos.y -= 400.f * DT;
		break;
	case DIR_RIGHT:
		vPos.x += m_Speed * DT;
		vPos.y -= 400.f * DT;
		break;
	}

	if (vPos.y <= m_DestroyPos.y - 10.f)
		DeleteObject(GetOwner());

	Transform()->SetRelativePos(vPos);
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
}

void CDiagonalPistolScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}