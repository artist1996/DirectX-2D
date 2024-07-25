#include "pch.h"
#include "CLevelSaveLoad.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Scripts/CScriptMgr.h>

void CLevelSaveLoad::SaveLevel(const wstring& _FilePath, CLevel* _pLevel)
{
	assert(_pLevel && _pLevel->GetState() == LEVEL_STATE::STOP);
	
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

	UINT i = 0;

	// Save Component Info
	for (; i < (UINT)COMPONENT_TYPE::END; ++i)
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

	// Component Type END 저장
	fwrite(&i, sizeof(COMPONENT_TYPE), 1, _pFile);

	// Save Script Info
	const vector<CScript*>& vecScripts = _Object->GetScripts();
	size_t ScriptCount = vecScripts.size();
	fwrite(&ScriptCount, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Save Script Name
		wstring strScriptName = CScriptMgr::GetScriptName(vecScripts[i]);
		SaveWString(strScriptName, _pFile);

		vecScripts[i]->SaveToFile(_pFile);
	}

	// Save ChildObject Info
	const vector<CGameObject*> vecChild = _Object->GetChildren();
	size_t ChildCount = vecChild.size();
	fwrite(&ChildCount, sizeof(size_t), 1, _pFile);

	// 재귀함수를 통해 Child 를 전부 저장
	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		SaveGameObject(_pFile, vecChild[i]);
	}
}
CLevel* CLevelSaveLoad::LoadLevel(const wstring& _FilePath)
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
	COMPONENT_TYPE Type = COMPONENT_TYPE::END;
	
	// 저장 되어있는 Type 값을 반복문을 돌며 확인한다
	while (true)
	{
		fread(&Type, sizeof(COMPONENT_TYPE), 1, _pFile);

		if (COMPONENT_TYPE::END == Type)
			break;

		CComponent* pComponent = GetComponent(Type);

		pObject->AddComponent(pComponent);

		pComponent->LoadFromFile(_pFile);
	}

	// Load Script
	size_t ScriptCount = 0;
	fread(&ScriptCount, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Load Script Name
		wstring strScriptName;
		LoadWString(strScriptName, _pFile);

		CScript* pScript = CScriptMgr::GetScript(strScriptName);
		pScript->LoadFromFile(_pFile);
		pObject->AddComponent(pScript);
	}

	// Load Child Object
	size_t ChildCount = 0;
	fread(&ChildCount, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < ChildCount; ++i)
	{
		CGameObject* pChildObject =	LoadGameObject(_pFile);
		pObject->AddChild(pChildObject);
	}
	
	return pObject;
}

CComponent* CLevelSaveLoad::GetComponent(COMPONENT_TYPE _Type)
{
	switch (_Type)
	{
	case COMPONENT_TYPE::TRANSFORM:
		return new CTransform;
	case COMPONENT_TYPE::COLLIDER2D:
		return new CCollider2D;
	case COMPONENT_TYPE::COLLIDER3D:
		break;
	case COMPONENT_TYPE::LIGHT2D:
		return new CLight2D;
	case COMPONENT_TYPE::LIGHT3D:
		break;
	case COMPONENT_TYPE::ANIMATOR2D:
		return new CAnimator2D;
	case COMPONENT_TYPE::ANIMATOR3D:
		break;
	case COMPONENT_TYPE::STATE_MACHINE:
		break;
	case COMPONENT_TYPE::RIGIDBODY:
		return new CRigidbody;
	case COMPONENT_TYPE::CAMERA:
		return new CCamera;
	case COMPONENT_TYPE::MESHRENDER:
		return new CMeshRender;
	case COMPONENT_TYPE::TILEMAP:
		return new CTileMap;
	case COMPONENT_TYPE::PARTICLE_SYSTEM:
		break;
	case COMPONENT_TYPE::DECAl:
		break;
	case COMPONENT_TYPE::SKYBOX:
		break;
	case COMPONENT_TYPE::LANDSCAPE:
		break;
	}
	return nullptr;
}
