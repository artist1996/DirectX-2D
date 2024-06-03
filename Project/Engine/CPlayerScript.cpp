#include "pch.h"
#include "CPlayerScript.h"

CPlayerScript::CPlayerScript()
	: m_Speed(200.f)
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
		DrawDebugCircle(Transform()->GetRelativePos(), 100.f, Vec4(0.f, 1.f, 0.f, 1.f), 3.f, false);
		//DrawDebugRect(Transform()->GetWorldMatrix(), Vec4(0.f, 1.f, 0.f, 1.f), 3.f, true);
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