#include "pch.h"
#include "CPlayerMoveScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CObjectPoolMgr.h>

#include <Engine/CTransform.h>
#include <Engine/CAnimator2D.h>

#include "CPlayerScript.h"

CPlayerMoveScript::CPlayerMoveScript()
	: CScript(SCRIPT_TYPE::PLAYERMOVESCRIPT)
{
}

CPlayerMoveScript::~CPlayerMoveScript()
{
}

void CPlayerMoveScript::Begin()
{

}

void CPlayerMoveScript::Tick()
{
}

void CPlayerMoveScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerMoveScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerMoveScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerMoveScript::SaveToFile(FILE* _pFile)
{
}

void CPlayerMoveScript::LoadFromFile(FILE* _pFile)
{
}