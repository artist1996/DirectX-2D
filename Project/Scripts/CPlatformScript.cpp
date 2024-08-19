#include "pch.h"
#include "CPlatformScript.h"

CPlatformScript::CPlatformScript()
	: CScript(SCRIPT_TYPE::PLATFORMSCRIPT)
	, m_Type(PLATFORM_TYPE::END)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_Type);
}

CPlatformScript::~CPlatformScript()
{
}

void CPlatformScript::Tick()
{
}

void CPlatformScript::SaveToFile(FILE* _pFile)
{
}

void CPlatformScript::LoadFromFile(FILE* _pFile)
{
}

void CPlatformScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (PLATFORM_TYPE::LEFT == m_Type)
	{
		if (L"PlayerMove" == _OtherObj->GetName())
			_OtherObj->SetMoveable(PLATFORM_TYPE::LEFT, false);
	}
	if (PLATFORM_TYPE::UP == m_Type)
	{
		if (L"PlayerMove" == _OtherObj->GetName())
			_OtherObj->SetMoveable(PLATFORM_TYPE::UP, false);
	}
	if (PLATFORM_TYPE::RIGHT == m_Type)
	{
		if (L"PlayerMove" == _OtherObj->GetName())
			_OtherObj->SetMoveable(PLATFORM_TYPE::RIGHT, false);
	}
	if (PLATFORM_TYPE::BOTTOM == m_Type)
	{
		if (L"PlayerMove" == _OtherObj->GetName())
			_OtherObj->SetMoveable(PLATFORM_TYPE::BOTTOM, false);
	}
}

void CPlatformScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (PLATFORM_TYPE::LEFT == m_Type)
	{
		if (L"PlayerMove" == _OtherObj->GetName())
			_OtherObj->SetMoveable(PLATFORM_TYPE::LEFT, true);
	}
	if (PLATFORM_TYPE::UP == m_Type)
	{
		if (L"PlayerMove" == _OtherObj->GetName())
			_OtherObj->SetMoveable(PLATFORM_TYPE::UP, true);
	}
	if (PLATFORM_TYPE::RIGHT == m_Type)
	{
		if (L"PlayerMove" == _OtherObj->GetName())
			_OtherObj->SetMoveable(PLATFORM_TYPE::RIGHT, true);
	}
	if (PLATFORM_TYPE::BOTTOM == m_Type)
	{
		if (L"PlayerMove" == _OtherObj->GetName())
			_OtherObj->SetMoveable(PLATFORM_TYPE::BOTTOM, true);
	}
}
