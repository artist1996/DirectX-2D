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
	if (L"PlayerMove" == _OtherObj->GetName())
	{
		Vec3 vPos = _OwnCollider->GetWorldPos();
		Vec3 vScale = Transform()->GetWorldScale();
		Vec3 vPlayerPos = _OtherCollider->GetWorldPos();
		Vec3 vPlayerScale = _OtherCollider->GetScale();
	
		bool* bMoveable = _OtherObj->GetMoveable();
		if (vPlayerPos.x + vPlayerScale.x * 0.5f < vPos.x - vScale.x * 0.5f - 10.f
			&& bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
		{
			_OtherObj->SetMoveable(PLATFORM_TYPE::RIGHT, false);
		}
	
		else if (vPlayerPos.x - vPlayerScale.x * 0.5f > vPos.x + vScale.x * 0.5f + 10.f
			&& bMoveable[(UINT)PLATFORM_TYPE::LEFT])
		{
			_OtherObj->SetMoveable(PLATFORM_TYPE::LEFT, false);
		}
	
		else if (vPlayerPos.y - vPlayerScale.y * 0.5f > vPos.y + vScale.y * 0.5f
			&& bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
		{
			_OtherObj->SetMoveable(PLATFORM_TYPE::BOTTOM, false);
		}
	
		else if (vPlayerPos.y + vPlayerScale.y * 0.5f < vPos.y - vScale.y * 0.5f
			&& bMoveable[(UINT)PLATFORM_TYPE::UP])
		{
			_OtherObj->SetMoveable(PLATFORM_TYPE::UP, false);
		}
	}
}

void CPlatformScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"PlayerMove" == _OtherObj->GetName())
	{
		Vec3 vPos = _OwnCollider->GetWorldPos();
		Vec3 vScale = Transform()->GetWorldScale();
		Vec3 vPlayerPos = _OtherCollider->GetWorldPos();
		Vec3 vPlayerScale = _OtherCollider->GetScale();

		bool* bMoveable = _OtherObj->GetMoveable();
		if (vPlayerPos.x + vPlayerScale.x * 0.5f < vPos.x - vScale.x * 0.5f - 10.f
			&& bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
		{
			_OtherObj->SetMoveable(PLATFORM_TYPE::RIGHT, false);
		}

		else if (vPlayerPos.x - vPlayerScale.x * 0.5f > vPos.x + vScale.x * 0.5f + 10.f
			&& bMoveable[(UINT)PLATFORM_TYPE::LEFT])
		{
			_OtherObj->SetMoveable(PLATFORM_TYPE::LEFT, false);
		}

		else if (vPlayerPos.y - vPlayerScale.y * 0.5f > vPos.y + vScale.y * 0.5f
			&& bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
		{
			_OtherObj->SetMoveable(PLATFORM_TYPE::BOTTOM, false);
		}

		else if (vPlayerPos.y + vPlayerScale.y * 0.5f < vPos.y - vScale.y * 0.5f
			&& bMoveable[(UINT)PLATFORM_TYPE::UP])
		{
			_OtherObj->SetMoveable(PLATFORM_TYPE::UP, false);
		}
	}
}

void CPlatformScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	_OtherObj->SetMoveable(PLATFORM_TYPE::LEFT, true);
	_OtherObj->SetMoveable(PLATFORM_TYPE::RIGHT, true);
	_OtherObj->SetMoveable(PLATFORM_TYPE::BOTTOM, true);
	_OtherObj->SetMoveable(PLATFORM_TYPE::UP, true);
}

void CPlatformScript::SaveToFile(FILE* _pFile)
{
}

void CPlatformScript::LoadFromFile(FILE* _pFile)
{
}

