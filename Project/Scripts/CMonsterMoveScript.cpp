#include "pch.h"
#include "CMonsterMoveScript.h"

CMonsterMoveScript::CMonsterMoveScript()
	: CScript(SCRIPT_TYPE::MONSTERMOVESCRIPT)
	, m_Speed(0.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Speed", &m_Speed);
}

CMonsterMoveScript::~CMonsterMoveScript()
{
}

void CMonsterMoveScript::Begin()
{
}

void CMonsterMoveScript::Tick()
{
	//GetOwner()->GetParent()->GetState();
}

void CMonsterMoveScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CMonsterMoveScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"PlayerMove" == _OtherObj->GetName())
		GetOwner()->SetGroundCollision(true);
}

void CMonsterMoveScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"PlayerMove" == _OtherObj->GetName())
		GetOwner()->SetGroundCollision(false);
}

void CMonsterMoveScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Speed, sizeof(float), 1, _pFile);
}

void CMonsterMoveScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Speed, sizeof(float), 1, _pFile);
}
