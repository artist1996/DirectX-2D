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

	if (KEY_PRESSED(KEY::Z))
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_0, 1);

		//Vec3 vRot = Transform()->GetRelativeRotation();
		//vRot.y += XM_PI * DT;
		//Transform()->SetRelativeRotation(vRot);
	}

	else
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_0, 0);
	}

	Transform()->SetRelativePos(vPos);
}