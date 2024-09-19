#include "pch.h"
#include "CNamedMonsterFaceHUDScript.h"

CNamedMonsterFaceHUDScript::CNamedMonsterFaceHUDScript()
	: CScript(SCRIPT_TYPE::NAMEDMONSTERFACEHUDSCRIPT)
{
}

CNamedMonsterFaceHUDScript::~CNamedMonsterFaceHUDScript()
{
}

void CNamedMonsterFaceHUDScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	GetOwner()->SetActive(false);
}

void CNamedMonsterFaceHUDScript::Tick()
{
	if (nullptr == GetOwner()->GetParent()->GetTarget())
		return;

	SetTexture();
}

void CNamedMonsterFaceHUDScript::SetTexture()
{
	const wstring& strName = GetOwner()->GetParent()->GetTarget()->GetName();

	if (L"hyungteo" == strName)
	{
		MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\enemyface\\hyungteoface.png"));
	}

	else if (L"juris" == strName)
	{
		MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\enemyface\\jurisface.png"));
	}

	else if (L"meltknight" == strName)
	{
		MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\enemyface\\meltknightface.png"));
	}
}

void CNamedMonsterFaceHUDScript::SaveToFile(FILE* _pFile)
{
}

void CNamedMonsterFaceHUDScript::LoadFromFile(FILE* _pFile)
{
}