#include "pch.h"
#include "CBuffScript.h"

#include <Engine/CLevelMgr.h>

CBuffScript::CBuffScript()
	: CScript(SCRIPT_TYPE::BUFFSCRIPT)
{
}

CBuffScript::~CBuffScript()
{
}

void CBuffScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	Animator2D()->Play(0, 20.f, false);
}

void CBuffScript::Tick()
{
	if (Animator2D()->IsFinish())
		DeleteObject(GetOwner());
}

void CBuffScript::SaveToFile(FILE* _pFile)
{
}

void CBuffScript::LoadFromFile(FILE* _pFile)
{
}