#include "pch.h"
#include "CLoadingScript.h"

CLoadingScript::CLoadingScript()
	: CScript(SCRIPT_TYPE::LOADINGSCRIPT)
	, m_Rot(0.f)
{
}

CLoadingScript::~CLoadingScript()
{
}

void CLoadingScript::Begin()
{
}

void CLoadingScript::Tick()
{
	m_Rot += DT * 3.f;

	Transform()->SetRelativeRotation(Vec3(0.f, 0.f, -m_Rot));
}