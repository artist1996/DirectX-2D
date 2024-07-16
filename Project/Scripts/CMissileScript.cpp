#include "pch.h"
#include "CMissileScript.h"

CMissileScript::CMissileScript()
	: CScript(SCRIPT_TYPE::MISSILESCRIPT)
	, m_Speed(1000.f)
{
}

CMissileScript::~CMissileScript()
{
}

void CMissileScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	vPos.y += m_Speed * DT;

	Transform()->SetRelativePos(vPos);
}

void CMissileScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"Monster" == _OtherObj->GetName())
	{
		DeleteObject(_OtherObj);
	}
}

void CMissileScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CMissileScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
