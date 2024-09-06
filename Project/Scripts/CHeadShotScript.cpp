#include "pch.h"
#include "CHeadShotScript.h"


CHeadShotScript::CHeadShotScript()
	: CScript(SCRIPT_TYPE::HEADSHOTSCRIPT)
	, m_HitEffectPref(nullptr)
{
}

CHeadShotScript::~CHeadShotScript()
{
}

void CHeadShotScript::Begin()
{
	m_HitEffectPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\headshothiteffect.pref");

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

void CHeadShotScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		Vec3 vPos = Transform()->GetWorldPos();
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();

		if (50.f > fabs(vPos.z - vOtherPos.z))
		{
			CGameObject* pObject = m_HitEffectPref->Instantiate();

			if (GetOwner()->GetDir() == OBJ_DIR::DIR_LEFT)
			{
				pObject->Transform()->SetRelativePos(Vec3(vOtherPos.x - 100.f, vOtherPos.y, vOtherPos.z - 50.f));
				pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
			}
			else if (GetOwner()->GetDir() == OBJ_DIR::DIR_RIGHT)
			{
				pObject->Transform()->SetRelativePos(Vec3(vOtherPos.x + 100.f, vOtherPos.y, vOtherPos.z - 50.f));
				pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
			}
			CreateObject(pObject, 0);
			DisconnectObject(GetOwner());
		}
	}
}