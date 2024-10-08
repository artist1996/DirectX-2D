#include "pch.h"
#include "CDeathCrisisGunHawkTwoScript.h"

CDeathCrisisGunHawkTwoScript::CDeathCrisisGunHawkTwoScript()
	: CScript(SCRIPT_TYPE::DEATHCRISISGUNHAWKTWOSCRIPT)
{
}

CDeathCrisisGunHawkTwoScript::~CDeathCrisisGunHawkTwoScript()
{
}

void CDeathCrisisGunHawkTwoScript::Begin()
{
	m_StartPos = Transform()->GetWorldPos();
	Vec3 vRot = Transform()->GetRelativeRotation();
	m_Dir = vRot.Normalize();

	Animator2D()->Play(0, 30.f, true);
	GetOwner()->GetChildren()[0]->Animator2D()->Play(0, 30.f, true);
}

void CDeathCrisisGunHawkTwoScript::Tick()
{	
	Vec3 vPos = Transform()->GetRelativePos();

	vPos += m_Dir * 2000.f * DT;

	if (2500.f < fabs(vPos.x - m_StartPos.x))
		DeleteObject(GetOwner()->GetParent());

	Transform()->SetRelativePos(vPos);
}

float CDeathCrisisGunHawkTwoScript::EaseInOut(float _x)
{
	return -(cosf(XM_PI * _x) - 1.f) / 2.f;
}

void CDeathCrisisGunHawkTwoScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		INFO& info = _OtherObj->GetInfo();
		info.HP -= 10.f;
	}
}

void CDeathCrisisGunHawkTwoScript::SaveToFile(FILE* _pFile)
{
}

void CDeathCrisisGunHawkTwoScript::LoadFromFile(FILE* _pFile)
{
}