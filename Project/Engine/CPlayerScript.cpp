#include "pch.h"
#include "CPlayerScript.h"

#include "CMissileScript.h"

CPlayerScript::CPlayerScript()
	: m_Speed(500.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::RIGHT))
		vPos.x += m_Speed * DT;
	if (KEY_PRESSED(KEY::LEFT))
		vPos.x -= m_Speed * DT;
	if (KEY_PRESSED(KEY::UP))
		vPos.y += m_Speed * DT;
	if (KEY_PRESSED(KEY::DOWN))
		vPos.y -= m_Speed * DT;
	if (KEY_TAP(KEY::SPACE))
	{
		//DrawDebugCircle(Transform()->GetRelativePos(), 100.f, Vec4(0.f, 1.f, 0.f, 1.f), 3.f, false);
		//DrawDebugRect(Transform()->GetWorldMatrix(), Vec4(0.f, 1.f, 0.f, 1.f), 3.f, true);

		CGameObject* pMissile = new CGameObject;
		pMissile->AddComponent(new CTransform);
		pMissile->AddComponent(new CMeshRender);
		pMissile->AddComponent(new CCollider2D);
		pMissile->AddComponent(new CMissileScript);

		Vec3 vMissilePos = Transform()->GetRelativePos();
		vMissilePos.y += Transform()->GetRelativeScale().y / 2.f;

		pMissile->Transform()->SetRelativePos(vMissilePos);
		pMissile->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

		pMissile->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

		CreateObject(pMissile, 5);
	}
	if (KEY_PRESSED(KEY::Z))
	{
		//MeshRender()->GetMaterial()->SetScalarParam(INT_0, 1);

		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.z += XM_PI * DT;
		Transform()->SetRelativeRotation(vRot);
	}

	else
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_0, 0);
	}

	Transform()->SetRelativePos(vPos);
}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	//if (L"Monster" == _OtherObj->GetName())
	//{
	//	DeleteObject(_OtherObj);
	//}
}
