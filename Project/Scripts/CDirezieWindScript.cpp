#include "pch.h"
#include "CDirezieWindScript.h"

CDirezieWindScript::CDirezieWindScript()
	: CScript(SCRIPT_TYPE::DIREZIEWINDSCRIPT)
	, m_Time(0.f)
{
}

CDirezieWindScript::~CDirezieWindScript()
{
}

void CDirezieWindScript::Begin()
{
	GetOwner()->SetDir(OBJ_DIR::DIR_LEFT);
	Animator2D()->Play(0.f, 10.f, true);
}

void CDirezieWindScript::Tick()
{
	m_Time += DT;

	if (7.f < m_Time)
	{
		OBJ_DIR Dir = GetOwner()->GetDir();

		if (OBJ_DIR::DIR_LEFT == Dir)
		{
			Transform()->SetRelativePos(Vec3(503.f, -104.f, 0.f));
			Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

			GetOwner()->SetDir(OBJ_DIR::DIR_RIGHT);
		}

		else if (OBJ_DIR::DIR_RIGHT == Dir)
		{
			Transform()->SetRelativePos(Vec3(-204.f, -104.f, 0.f));
			Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));

			GetOwner()->SetDir(OBJ_DIR::DIR_LEFT);
		}

		m_Time = 0.f;
	}

	
}

void CDirezieWindScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDirezieWindScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		m_HitTime += DT;

		if (1.f < m_HitTime)
		{
			INFO& info = _OtherObj->GetInfo();
			info.HP -= 50.f;

			m_HitTime = 0.f;
		}
	}
}

void CDirezieWindScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}