#include "pch.h"
#include "CUICameraScript.h"

#include <Engine/CLevelMgr.h>

CUICameraScript::CUICameraScript()
	: CScript(SCRIPT_TYPE::UICAMERASCRIPT)
{
}

CUICameraScript::~CUICameraScript()
{
}

void CUICameraScript::Begin()
{
	m_Target = CLevelMgr::GetInst()->FindObjectByName(L"MainCamera");
}

void CUICameraScript::Tick()
{
	//Vec3 vTargetPos = m_Target->Transform()->GetWorldPos();
	//
	//Transform()->SetRelativePos(vTargetPos);
}

void CUICameraScript::SaveToFile(FILE* _pFile)
{
}

void CUICameraScript::LoadFromFile(FILE* _pFile)
{
}