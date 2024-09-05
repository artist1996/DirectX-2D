#include "pch.h"
#include "CPlatformScript.h"

CPlatformScript::CPlatformScript()
	: CScript(SCRIPT_TYPE::PLATFORMSCRIPT)
	, m_PrevFrame(false)
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
		Vec3 vOtherPos = _OtherCollider->GetWorldPos();
		Vec3 vOtherScale = _OtherObj->Transform()->GetWorldScale();

		bool* bMoveable = _OtherObj->GetMoveable();

		if (vOtherPos.x + vOtherScale.x * 0.5f < vPos.x - vScale.x * 0.5f + 10.f
			&& vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f
			&& vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f)
		{
			_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::RIGHT, false);
		}

		else if (vOtherPos.x - vOtherScale.x * 0.5f > vPos.x + vScale.x * 0.5f - 10.f
			&& vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f
			&& vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f)
		{
			_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::LEFT, false);
		}
		
		else if (vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f - 10.f
			&& vOtherPos.x - vOtherScale.x * 0.5f > vPos.x - vScale.x * 0.5f
			&& vOtherPos.x + vOtherScale.x * 0.5f < vPos.x + vScale.x * 0.5f)
		{
			_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::UP, false);
		}

		else if (vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f + 10.f
			&& vOtherPos.x - vOtherScale.x * 0.5f > vPos.x - vScale.x * 0.5f
			&& vOtherPos.x + vOtherScale.x * 0.5f < vPos.x + vScale.x * 0.5f)
		{
			_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::BOTTOM, false);
		}
	}
}

void CPlatformScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{	
	if (L"PlayerMove" == _OtherObj->GetName())
	{
		Vec3 vPos = _OwnCollider->GetWorldPos();
		Vec3 vScale = Transform()->GetWorldScale();
		Vec3 vOtherPos = _OtherCollider->GetWorldPos();
		Vec3 vOtherScale = _OtherObj->Transform()->GetWorldScale();
		
		bool* bMoveable = _OtherObj->GetMoveable();
		
		if (vOtherPos.x + vOtherScale.x * 0.5f < vPos.x - vScale.x * 0.5f + 10.f
			&& vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f
			&& vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f)
		{
			_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::RIGHT, false);
		}
		
		else if (vOtherPos.x - vOtherScale.x * 0.5f > vPos.x + vScale.x * 0.5f - 10.f
			&& vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f
			&& vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f)
		{
			_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::LEFT, false);
		}
		
		else if (vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f - 10.f
			&& vOtherPos.x - vOtherScale.x * 0.5f > vPos.x - vScale.x * 0.5 - 100.f
			&& vOtherPos.x + vOtherScale.x * 0.5f < vPos.x + vScale.x * 0.5f + 100.f)
		{
			_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::UP, false);
		}
		
		else if (vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f + 10.f
			&& vOtherPos.x - vOtherScale.x * 0.5f > vPos.x - vScale.x * 0.5f - 100.f
			&& vOtherPos.x + vOtherScale.x * 0.5f < vPos.x + vScale.x * 0.5f + 100.f)
		{
			_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::BOTTOM, false);
		}
	}
}

void CPlatformScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"PlayerMove" == _OtherObj->GetName())
	{
		_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::LEFT, true);
		_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::RIGHT, true);
		_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::BOTTOM, true);
		_OtherObj->GetParent()->SetMoveable(PLATFORM_TYPE::UP, true);
	}
}

void CPlatformScript::SaveToFile(FILE* _pFile)
{
}

void CPlatformScript::LoadFromFile(FILE* _pFile)
{
}

