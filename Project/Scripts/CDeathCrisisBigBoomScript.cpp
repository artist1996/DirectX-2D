#include "pch.h"
#include "CDeathCrisisBigBoomScript.h"

CDeathCrisisBigBoomScript::CDeathCrisisBigBoomScript()
	: CScript(SCRIPT_TYPE::DEATHCRISISBIGBOOMSCRIPT)
{
}

CDeathCrisisBigBoomScript::~CDeathCrisisBigBoomScript()
{
}

void CDeathCrisisBigBoomScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	Animator2D()->Play(0, 10.f, false);
}

void CDeathCrisisBigBoomScript::Tick()
{
	Vec3 vScale = Transform()->GetRelativeScale();

	if (0 == Animator2D()->GetCurFrameIndex())
		Transform()->SetRelativeScale(Vec3(500.f, 500.f, 1.f));
	else if (1 == Animator2D()->GetCurFrameIndex())
		Transform()->SetRelativeScale(Vec3(600.f, 600.f, 1.f));
	else if (2 == Animator2D()->GetCurFrameIndex())
		Transform()->SetRelativeScale(Vec3(700.f, 600.f, 1.f));
	else if (3 == Animator2D()->GetCurFrameIndex())
		Transform()->SetRelativeScale(Vec3(1500.f, 1500.f, 1.f));
	else if (4 == Animator2D()->GetCurFrameIndex())
		Transform()->SetRelativeScale(Vec3(3000.f, 3000.f, 1.f));
	else if (5 == Animator2D()->GetCurFrameIndex())
		Transform()->SetRelativeScale(Vec3(5000.f, 5000.f, 1.f));
	else if (6 == Animator2D()->GetCurFrameIndex())
		Transform()->SetRelativeScale(Vec3(30000.f, 30000.f, 1.f));
	else if (7 == Animator2D()->GetCurFrameIndex())
		Transform()->SetRelativeScale(Vec3(100000.f, 100000.f, 1.f));
	else if (8 == Animator2D()->GetCurFrameIndex())
		Transform()->SetRelativeScale(Vec3(0.f, 0.f, 1.f));
	else if (9 == Animator2D()->GetCurFrameIndex())
		Transform()->SetRelativeScale(Vec3(0.f, 0.f, 1.f));

	if (Animator2D()->IsFinish())
		DeleteObject(GetOwner());

}

void CDeathCrisisBigBoomScript::SaveToFile(FILE* _pFile)
{
}

void CDeathCrisisBigBoomScript::LoadFromFile(FILE* _pFile)
{
}

void CDeathCrisisBigBoomScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDeathCrisisBigBoomScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_hit_01.ogg")->Play(1, 0.2f, false);
		INFO& info = _OtherObj->GetInfo();
		info.HP -= 10.f;
	}
}

void CDeathCrisisBigBoomScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
