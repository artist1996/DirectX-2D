#include "pch.h"
#include "CHyungteoPunchScript.h"

CHyungteoPunchScript::CHyungteoPunchScript()
	: CScript(SCRIPT_TYPE::HYUNGTEOPUNCHSCRIPT)
	, m_Time(0.f)
{
}

CHyungteoPunchScript::~CHyungteoPunchScript()
{
}

void CHyungteoPunchScript::Begin()
{
}

void CHyungteoPunchScript::Tick()
{
	m_Time += DT;

	if (0.5f < m_Time)
		DeleteObject(GetOwner());
}

void CHyungteoPunchScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	//if (L"Player" == _OtherObj->GetName())
	//{
	//	INFO& info = _OtherObj->GetInfo();
	//	info.bHit = true;
	//}
}

void CHyungteoPunchScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CHyungteoPunchScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}