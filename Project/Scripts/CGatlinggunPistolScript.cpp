#include "pch.h"
#include "CGatlinggunPistolScript.h"

CGatlinggunPistolScript::CGatlinggunPistolScript()
	: CScript(SCRIPT_TYPE::GATLINGGUNPISTOLSCRIPT)
	, m_Speed(1000.f)
{
}

CGatlinggunPistolScript::~CGatlinggunPistolScript()
{
}

void CGatlinggunPistolScript::Begin()
{
}

void CGatlinggunPistolScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	OBJ_DIR Dir = GetOwner()->GetDir();

	if (OBJ_DIR::DIR_LEFT == Dir)
		vPos.x -= 1.f * m_Speed * DT;
	else
		vPos.x += 1.f * m_Speed * DT;

	vPos.y += 1.f * m_Speed * DT;


	Transform()->SetRelativePos(vPos);
}

void CGatlinggunPistolScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"hyungteo" == _OtherObj->GetName() || L"direzie" == _OtherObj->GetName())
	{
		INFO& info = _OtherObj->GetInfo();

		info.HP -= 5.f;
		_OtherObj->FSM()->ChangeState(L"HitBBQ");
		DeleteObject(GetOwner());
	}
}

void CGatlinggunPistolScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CGatlinggunPistolScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CGatlinggunPistolScript::SaveToFile(FILE* _pFile)
{
}

void CGatlinggunPistolScript::LoadFromFile(FILE* _pFile)
{
}
