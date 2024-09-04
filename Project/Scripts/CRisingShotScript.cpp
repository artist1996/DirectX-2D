#include "pch.h"
#include "CRisingShotScript.h"

CRisingShotScript::CRisingShotScript()
	: CScript(SCRIPT_TYPE::RISINGSHOTSCRIPT)
{
}

CRisingShotScript::~CRisingShotScript()
{
}

void CRisingShotScript::Begin()
{
	Animator2D()->Play(0, 10.f, true);

	if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
}

void CRisingShotScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	OBJ_DIR Dir = GetOwner()->GetDir();

	switch (Dir)
	{
	case OBJ_DIR::DIR_LEFT:
		vPos += Vec3(-1.f, 0.f, 0.f) * 1000.f * DT;
		break;
	case OBJ_DIR::DIR_RIGHT:
		vPos += Vec3(1.f, 0.f, 0.f) * 1000.f * DT;
		break;
	}

	if (800.f < fabs(GetOwner()->GetInitPos().x - vPos.x))
	{
		DeleteObject(GetOwner());
	}

	Transform()->SetRelativePos(vPos);
}