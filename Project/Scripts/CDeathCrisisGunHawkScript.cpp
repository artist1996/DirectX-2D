#include "pch.h"
#include "CDeathCrisisGunHawkScript.h"

#include <Engine/CLevelMgr.h>

CDeathCrisisGunHawkScript::CDeathCrisisGunHawkScript()
	: CScript(SCRIPT_TYPE::DEATHCRISISGUNHAWKSCRIPT)
{
}

CDeathCrisisGunHawkScript::~CDeathCrisisGunHawkScript()
{
}

void CDeathCrisisGunHawkScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	m_StartPos = Transform()->GetRelativePos();

	Vec3 vRot = Transform()->GetRelativeRotation();
	m_Dir = vRot.Normalize();
	Animator2D()->Play(0, 30.f, true);

}

void CDeathCrisisGunHawkScript::Tick()
{	
	Vec3 vPos = Transform()->GetRelativePos();
	
	vPos += m_Dir * 1500.f * DT;
	
	if (2000.f < fabs(vPos.x - m_StartPos.x))
		DeleteObject(GetOwner()->GetParent());
	
	Transform()->SetRelativePos(vPos);
}

void CDeathCrisisGunHawkScript::SaveToFile(FILE* _pFile)
{
}

void CDeathCrisisGunHawkScript::LoadFromFile(FILE* _pFile)
{
}

void CDeathCrisisGunHawkScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		INFO& info = _OtherObj->GetInfo();
		info.HP -= 10.f;
	}
}
