#include "pch.h"
#include "CDiagonalHeadShotScript.h"

CDiagonalHeadShotScript::CDiagonalHeadShotScript()
	: CScript(SCRIPT_TYPE::DIAGONALHEADSHOTSCRIPT)
	, m_HitEffectPref(nullptr)
	, m_Speed(700.f)
	, m_DestroyPos(0.f)
{
}

CDiagonalHeadShotScript::~CDiagonalHeadShotScript()
{
}

void CDiagonalHeadShotScript::Begin()
{
	m_HitEffectPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\headshothiteffect.pref");
	Animator2D()->Play(0, 10.f, true);

	if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
	{
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI / 3.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetDir())
	{
		Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
	}
}

void CDiagonalHeadShotScript::Tick()
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

void CDiagonalHeadShotScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx() || L"Platform" == _OtherObj->GetName())
	{
		Vec3 vPos = Transform()->GetWorldPos();
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();

		if (GetOwner()->GetParent()->GetGroundCollision() && L"MonsterMove" != _OtherObj->GetName())
		{
			CGameObject* pObject = m_HitEffectPref->Instantiate();
			INFO& info = _OtherObj->GetInfo();
			info.HP -= 10.f;
			if (GetOwner()->GetParent()->GetDir() == OBJ_DIR::DIR_LEFT)
			{
				pObject->Transform()->SetRelativePos(Vec3(vOtherPos.x - 150.f, vOtherPos.y, vOtherPos.z - 50.f));
				pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
			}
			else if (GetOwner()->GetParent()->GetDir() == OBJ_DIR::DIR_RIGHT)
			{
				pObject->Transform()->SetRelativePos(Vec3(vOtherPos.x + 150.f, vOtherPos.y, vOtherPos.z - 50.f));
				pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
			}
			CreateObject(pObject, 0);
			//DeleteObject(GetOwner()->GetParent());

			if (L"hyungteo" == _OtherObj->GetName())
			{
				if (_OtherObj->Rigidbody()->IsGround())
					_OtherObj->FSM()->ChangeState(L"Hit");
			}
			else if (L"juris" == _OtherObj->GetName())
			{
				_OtherObj->FSM()->ChangeState(L"Hit");
			}
		}
	}
}