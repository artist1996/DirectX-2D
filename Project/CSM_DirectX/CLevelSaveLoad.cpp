#include "pch.h"
#include "CLevelSaveLoad.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Scripts/CScriptMgr.h>

void CLevelSaveLoad::LevelSave(const wstring& _FilePath, CLevel* _pLevel)
{
	assert(_pLevel);
	
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"wb");

	if (nullptr == pFile)
		return;

	SaveWString(_pLevel->GetName(), pFile);

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = _pLevel->GetLayer(i);

		// Save Layer Name
		SaveWString(pLayer->GetName(), pFile);

		// Layer 안의 Parent GameObject Save
		const vector<CGameObject*>& vecParents = pLayer->GetParentObjects();

		size_t count = vecParents.size();
		fwrite(&count, sizeof(size_t), 1, pFile);

		for (size_t i = 0; i < vecParents.size(); ++i)
		{
			SaveGameObject(pFile, vecParents[i]);
		}
	}

	fclose(pFile);
}

void CLevelSaveLoad::SaveGameObject(FILE* _pFile, CGameObject* _Object)
{
	// Object Name
	SaveWString(_Object->GetName(), _pFile);

	// Save Component Info
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		CComponent* pComponent = _Object->GetComponent((COMPONENT_TYPE)i);
		
		if (nullptr == pComponent)
			continue;

		// Save Component Type
		COMPONENT_TYPE Type = pComponent->GetComponentType();
		fwrite(&Type, sizeof(COMPONENT_TYPE), 1, _pFile);

		// Save Component
		pComponent->SaveToFile(_pFile);
	}

	// Save Script Info
	const vector<CScript*>& vecScripts = _Object->GetScripts();
	size_t ScriptCount = vecScripts.size();

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Save Script Name
		wstring strScriptName = CScriptMgr::GetScriptName(vecScripts[i]);
		SaveWString(strScriptName, _pFile);

		vecScripts[i]->SaveToFile(_pFile);
	}

	// Save ChildObject Info
}

CLevel* CLevelSaveLoad::LevelLoad(const wstring& _FilePath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"rb");
	
	if (nullptr == pFile)
		return nullptr;
	
	// Level 생성
	CLevel* pLevel = new CLevel;

	// Load Level Name
	wstring strLevelName;
	LoadWString(strLevelName, pFile);
	pLevel->SetName(strLevelName);

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pLevel->GetLayer(i);

		// Load Layer Name
		wstring strLayerName;
		LoadWString(strLayerName, pFile);
		pLayer->SetName(strLayerName);

		// Load ParentObject Count
		size_t ObjectCount = 0;
		fread(&ObjectCount, sizeof(size_t), 1, pFile);

		for (size_t i = 0; i < ObjectCount; ++i)
		{
			CGameObject* pObject = LoadGameObject(pFile);
			pLayer->AddObject(pObject, false);
		}
	}

	return pLevel;
}

CGameObject* CLevelSaveLoad::LoadGameObject(FILE* _pFile)
{
	CGameObject* pObject = new CGameObject;

	wstring strName;
	LoadWString(strName, _pFile);
	pObject->SetName(strName);
	
	// Load Component Info
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		COMPONENT_TYPE Type;
		fread(&Type, sizeof(COMPONENT_TYPE), 1, _pFile);

		switch (Type)
		{
		case COMPONENT_TYPE::TRANSFORM:
		{
			CTransform* pTrans = new CTransform;
			pTrans->LoadFromFile(_pFile);
			pObject->AddComponent(pTrans);
		}
			break;
		case COMPONENT_TYPE::COLLIDER2D:
		{
			CCollider2D* pCollider2D = new CCollider2D;
			pCollider2D->LoadFromFile(_pFile);
			pObject->AddComponent(pCollider2D);
		}
			break;
		case COMPONENT_TYPE::LIGHT2D:
		{
			CLight2D* pLight2D = new CLight2D;
			pLight2D->LoadFromFile(_pFile);
			pObject->AddComponent(pLight2D);
		}
			break;
		case COMPONENT_TYPE::ANIMATOR2D:
		{
			CAnimator2D* pAnimator2D = new CAnimator2D;
			pAnimator2D->LoadFromFile(_pFile);
			pObject->AddComponent(pAnimator2D);
		}
			break;
		case COMPONENT_TYPE::RIGIDBODY:
		{
			CRigidbody* pRB = new CRigidbody;
			pRB->LoadFromFile(_pFile);
			pObject->AddComponent(pRB);
		}
			break;
		case COMPONENT_TYPE::CAMERA:
		{
			CCamera* pCamera = new CCamera;
			pCamera->LoadFromFile(_pFile);
			pObject->AddComponent(pCamera);
		}
			break;
		case COMPONENT_TYPE::MESHRENDER:
		{
			CMeshRender* pMeshRender = new CMeshRender;
			pMeshRender->LoadFromFile(_pFile);
			pObject->AddComponent(pMeshRender);
		}
			break;
		case COMPONENT_TYPE::TILEMAP:
		{
			CTileMap* pTileMap = new CTileMap;
			pTileMap->LoadFromFile(_pFile);
			pObject->AddComponent(pTileMap);
		}
			break;
		case COMPONENT_TYPE::PARTICLE_SYSTEM:
			break;
		}
	}

	// Load Script
	size_t ScriptCount = 0;
	fread(&ScriptCount, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		wstring strName;
		LoadWString(strName, _pFile);
		CScript* pScript = CScriptMgr::GetScript(strName);
		pScript->LoadFromFile(_pFile);
		pObject->AddComponent(pScript);
	}

	// Load Child Object


	return pObject;
}
