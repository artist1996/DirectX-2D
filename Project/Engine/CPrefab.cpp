#include "pch.h"
#include "CPrefab.h"
#include "CGameObject.h"

CPrefab::CPrefab()
	: CAsset(ASSET_TYPE::PREFAB)
	, m_ProtoObject(nullptr)
{
}

CPrefab::~CPrefab()
{
	if (nullptr != m_ProtoObject)
		delete m_ProtoObject;
}

CGameObject* CPrefab::Instantiate()
{
	return m_ProtoObject->Clone();
}

int CPrefab::Save(const wstring& _FilePath)
{
	return 0;
}

int CPrefab::Load(const wstring& _FilePath)
{
	return 0;
}
