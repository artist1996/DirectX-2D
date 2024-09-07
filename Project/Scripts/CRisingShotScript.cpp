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

void CRisingShotScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"hyungteo" == _OtherObj->GetName())
	{
		Vec3 vPos = Transform()->GetWorldPos();
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();

		Vec3 vDist = vOtherPos - vPos;

		if (100.f > fabs(vDist.z)
			&& 20.f < fabs(vDist.z))
		{
			CRigidbody* pRB = _OtherObj->Rigidbody();

			if (pRB->IsGround())
			{
				pRB->Rigidbody()->SetMaxGravitySpeed(800.f);
				pRB->Rigidbody()->SetJumpSpeed(700.f);
			}

			else
			{
				pRB->SetGround(true);
				pRB->Rigidbody()->SetGravityVelocity(Vec3(0.f, 0.f, 0.f));
				pRB->Rigidbody()->SetMaxGravitySpeed(600.f);
				pRB->Rigidbody()->SetJumpSpeed(600.f);
				pRB->Jump();
			}

			_OtherObj->FSM()->ChangeState(L"Fly");
		}
	}
}