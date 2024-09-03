#include "pch.h"
#include "CSeriaScript.h"

CSeriaScript::CSeriaScript()
	: CScript(SCRIPT_TYPE::SERIASCRIPT)
{
}

CSeriaScript::~CSeriaScript()
{
}

void CSeriaScript::Begin()
{
	Animator2D()->Play(0, 5.f, true);
}

void CSeriaScript::Tick()
{
}

void CSeriaScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}