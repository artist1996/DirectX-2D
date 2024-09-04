#include "pch.h"
#include "CHeadShotScript.h"

CHeadShotScript::CHeadShotScript()
	: CScript(SCRIPT_TYPE::HEADSHOTSCRIPT)
{
}

CHeadShotScript::~CHeadShotScript()
{
}

void CHeadShotScript::Begin()
{
	Animator2D()->Play(0, 10.f, true);
	Collider2D()->SetActive(true);

	if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
}

void CHeadShotScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	OBJ_DIR Dir = GetOwner()->GetDir();

	switch (Dir)
	{
	case OBJ_DIR::DIR_LEFT:
		vPos += Vec3(-1.f, 0.f,0.f) * 1000.f * DT;
		break;
	case OBJ_DIR::DIR_RIGHT:
		vPos += Vec3(1.f, 0.f, 0.f) * 1000.f * DT;
		break;
	}

	if (800.f < fabs(GetOwner()->GetInitPos().x - vPos.x))
	{
		DisconnectObject(GetOwner());
	}

	Transform()->SetRelativePos(vPos);
}