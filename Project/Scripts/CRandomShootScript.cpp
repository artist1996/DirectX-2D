#include "pch.h"
#include "CRandomShootScript.h"

CRandomShootScript::CRandomShootScript()
	: CScript(SCRIPT_TYPE::RANDOMSHOOTSCRIPT)
	, m_Count(0)
{
}

CRandomShootScript::~CRandomShootScript()
{
}

void CRandomShootScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetScalarParam(INT_3, 1);
	Animator2D()->Play(0, 17.f, false);
//#ifdef _DEBUG
//	Collider2D()->SetActive(true);
//#endif
	Collider2D()->SetActive(false);
}

void CRandomShootScript::Tick()
{
	if (Animator2D()->IsFinish())
	{
		DisconnectObject(GetOwner());
		Animator2D()->Reset();
	}
}

void CRandomShootScript::SaveToFile(FILE* _pFile)
{
}

void CRandomShootScript::LoadFromFile(FILE* _pFile)
{
}