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

	m_DestroyPos = GetOwner()->GetOwner()->Collider2D()->GetWorldPos().y - GetOwner()->GetOwner()->Collider2D()->GetScale().y * 0.5f;
}

void CDiagonalHeadShotScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	switch (GetOwner()->GetDir())
	{
	case OBJ_DIR::DIR_LEFT:
		vPos.x -= m_Speed * DT;
		vPos.y -= 400.f * DT;
		break;
	case OBJ_DIR::DIR_RIGHT:
		vPos.x += m_Speed * DT;
		vPos.y -= 400.f * DT;
		break;
	}

	if (vPos.y <= m_DestroyPos)
		DeleteObject(GetOwner());

	Transform()->SetRelativePos(vPos);
}

void CDiagonalHeadShotScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		Vec3 vPos = Transform()->GetWorldPos();
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();
		
		//Vec3 vPos = Transform()->GetWorldPos();
		//Vec3 vOtherPos = _OtherCollider->GetWorldMatrix().Translation();

		float heightDiff = vPos.y - vOtherPos.y;
		if (100.f > heightDiff && heightDiff > -20.f)
		{
			INFO& info = _OtherObj->GetInfo();
			info.HP -= 10.f;

			CGameObject* pObject = m_HitEffectPref->Instantiate();

			if (GetOwner()->GetDir() == OBJ_DIR::DIR_LEFT)
			{
				pObject->Transform()->SetRelativePos(Vec3(vOtherPos.x - 150.f, vOtherPos.y, -10000.f));
				pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));

			}
			else if (GetOwner()->GetDir() == OBJ_DIR::DIR_RIGHT)
			{
				pObject->Transform()->SetRelativePos(Vec3(vOtherPos.x + 150.f, vOtherPos.y, -10000.f));
				pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
			}

			CreateObject(pObject, 0);
			DeleteObject(GetOwner());

			if (L"hyungteo" == _OtherObj->GetName())
			{
				if (_OtherObj->Rigidbody()->IsGround())
					_OtherObj->FSM()->ChangeState(L"Hit");
			}
		}
	}
}