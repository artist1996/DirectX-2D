#include "pch.h"
#include "CPlatformScript.h"

CPlatformScript::CPlatformScript()
	: CScript(SCRIPT_TYPE::PLATFORMSCRIPT)
{
}

CPlatformScript::~CPlatformScript()
{
}

void CPlatformScript::Tick()
{
}

void CPlatformScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
		_OtherObj->Rigidbody()->SetGround(true);
}

void CPlatformScript::SaveToFile(FILE* _pFile)
{
}

void CPlatformScript::LoadFromFile(FILE* _pFile)
{
}
