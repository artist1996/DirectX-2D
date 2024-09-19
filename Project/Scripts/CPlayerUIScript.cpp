#include "pch.h"
#include "CPlayerUIScript.h"

#include <Engine/CLevelMgr.h>

CPlayerUIScript::CPlayerUIScript()
	: CScript(SCRIPT_TYPE::PLAYERUISCRIPT)
	, m_pTarget(nullptr)
{
}

CPlayerUIScript::~CPlayerUIScript()
{
}

void CPlayerUIScript::Begin()
{
	//m_pTarget = CLevelMgr::GetInst()->FindObjectByName(L"UICamera");
	//m_Offset = Vec2(0.f, -334.f);
}

void CPlayerUIScript::Tick()
{
	//Vec3 vTargetPos = m_pTarget->Transform()->GetRelativePos();
	//Transform()->SetRelativePos(Vec3(vTargetPos.x + m_Offset.x, vTargetPos.y + m_Offset.y, 0.f));
}

void CPlayerUIScript::SaveToFile(FILE* _pFile)
{
}

void CPlayerUIScript::LoadFromFile(FILE* _pFile)
{
}
