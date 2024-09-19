#include "pch.h"
#include "CPunisherPistolScript.h"

CPunisherPistolScript::CPunisherPistolScript()
	: CScript(SCRIPT_TYPE::PUNISHERPISTOLSCRIPT)
	, m_Speed(1000.f)
{
}

CPunisherPistolScript::~CPunisherPistolScript()
{
}

void CPunisherPistolScript::Begin()
{
	Animator2D()->Play(0.f, 7.f, true);
}

void CPunisherPistolScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	OBJ_DIR Dir = GetOwner()->GetDir();

	if (OBJ_DIR::DIR_LEFT == Dir)
		vPos.x -= 1.f * m_Speed * DT;
	else
		vPos.x += 1.f * m_Speed * DT;

	vPos.y += -1.f * m_Speed * DT;


	Transform()->SetRelativePos(vPos);
}

void CPunisherPistolScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"hyungteo" == _OtherObj->GetName())
	{
		INFO& info = _OtherObj->GetInfo();

		info.HP -= 15.f;

		_OtherObj->FSM()->ChangeState(L"DownHit");
		DeleteObject(GetOwner());
	}
	else if (L"direzie" == _OtherObj->GetName())
	{
		INFO& info = _OtherObj->GetInfo();

		info.HP -= 15.f;
		
		_OtherObj->Animator2D()->Play(10, 10.f, false);
		_OtherObj->FSM()->ChangeState(L"DownHit");
		DeleteObject(GetOwner());
	}
}

void CPunisherPistolScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPunisherPistolScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPunisherPistolScript::SaveToFile(FILE* _pFile)
{
}

void CPunisherPistolScript::LoadFromFile(FILE* _pFile)
{
}
