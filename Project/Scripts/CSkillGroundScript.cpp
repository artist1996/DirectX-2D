#include "pch.h"
#include "CSkillGroundScript.h"

CSkillGroundScript::CSkillGroundScript()
	: CScript(SCRIPT_TYPE::SKILLGROUNDSCRIPT)
{
}

CSkillGroundScript::~CSkillGroundScript()
{
}

void CSkillGroundScript::Begin()
{
}

void CSkillGroundScript::Tick()
{
}

void CSkillGroundScript::SaveToFile(FILE* _pFile)
{
}

void CSkillGroundScript::LoadFromFile(FILE* _pFile)
{
}

void CSkillGroundScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"MonsterMove" == _OtherObj->GetName() || L"Platform" == _OtherObj->GetName())
	{
		GetOwner()->SetGroundCollision(true);
	}
}