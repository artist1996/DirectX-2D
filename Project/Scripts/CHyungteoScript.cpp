#include "pch.h"
#include "CHyungteoScript.h"

#include <States/CHyungteoEatState.h>
#include <States/CHyungteoLookState.h>

CHyungteoScript::CHyungteoScript()
	: CScript(SCRIPT_TYPE::HYUNGTEOSCRIPT)
{
}

CHyungteoScript::~CHyungteoScript()
{
}

void CHyungteoScript::InitInfo()
{
	INFO Info = {};
	Info.MaxHP = 100;
	Info.HP = Info.MaxHP;
	Info.Defense = 0;
	Info.MinAttack = 10;
	Info.MaxAttack = 20;

	GetOwner()->SetInfo(Info);
}

void CHyungteoScript::Begin()
{
	InitInfo();

	FSM()->AddState(L"Eat", new CHyungteoEatState);
	FSM()->AddState(L"Look", new CHyungteoLookState);

	FSM()->ChangeState(L"Eat");
}

void CHyungteoScript::Tick()
{
}

void CHyungteoScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CHyungteoScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CHyungteoScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}