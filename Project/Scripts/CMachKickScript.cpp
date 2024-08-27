#include "pch.h"
#include "CMachKickScript.h"

CMachKickScript::CMachKickScript()
	: CScript(SCRIPT_TYPE::MACHKICKSCRIPT)
	, m_Time(0.f)
{
}

CMachKickScript::~CMachKickScript()
{
}

void CMachKickScript::Begin()
{
}

void CMachKickScript::Tick()
{
	m_Time += DT;

	if (0.1f < m_Time)
	{
		DeleteObject(GetOwner());
	}
}

void CMachKickScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}