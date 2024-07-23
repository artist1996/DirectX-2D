#include "pch.h"
#include "MenuUI.h"

#include <Engine/CAssetMgr.h>
#include <Engine/assets.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include <Engine/CScript.h>

#include <Scripts/CScriptMgr.h>

#include "Inspector.h"
#include "CEditorMgr.h"

MenuUI::MenuUI()
{
}

MenuUI::~MenuUI()
{
}


void MenuUI::Tick()
{
	if (!IsActive())
		return;

	if (ImGui::BeginMainMenuBar())
	{

		Update();

		ImGui::EndMainMenuBar();
	}
}

void MenuUI::Update()
{
	File();

	Level();

	GameObject();

	Assets();
}

void MenuUI::File()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Level Save"))
		{

		}

		if (ImGui::MenuItem("Level Load"))
		{

		}

		ImGui::EndMenu();
	}
}

void MenuUI::Level()
{
	if (ImGui::BeginMenu("Level"))
	{
		if (ImGui::MenuItem("Play"))
		{
			ChangeLevelState(PLAY);
		}

		if (ImGui::MenuItem("Pause"))
		{
			ChangeLevelState(PAUSE);
		}

		if (ImGui::MenuItem("Stop"))
		{
			ChangeLevelState(STOP);
		}

		ImGui::EndMenu();
	}
}

void MenuUI::GameObject()
{
	if (ImGui::BeginMenu("GameObject"))
	{
		if (ImGui::MenuItem("Create Empty Object"))
		{
		
		}

		AddComponent();

		AddScript();

		ImGui::EndMenu();
	}
}

void MenuUI::Assets()
{
	if (ImGui::BeginMenu("Assets"))
	{
		if (ImGui::MenuItem("Create Empty Material"))
		{
			Ptr<CMaterial> pMtrl = new CMaterial;
			wstring Key = GetAssetKey(ASSET_TYPE::MATERIAL, L"Default Material");
			CAssetMgr::GetInst()->AddAsset(Key, pMtrl);
			pMtrl->Save(Key);
		}

		if (ImGui::MenuItem("Create Empty Sprite"))
		{
			Ptr<CSprite> pSprite = new CSprite;
			wstring Key = GetAssetKey(ASSET_TYPE::SPRITE, L"Default Sprite");
			CAssetMgr::GetInst()->AddAsset(Key, pSprite);
			pSprite->Save(Key);
		}

		if (ImGui::MenuItem("Create Animation"))
		{
			CreateAnimation();
		}

		ImGui::EndMenu();
	}
}

void MenuUI::AddComponent()
{
	if (ImGui::BeginMenu("Add Component"))
	{
		if (ImGui::MenuItem("Transform"))
		{
			Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
			CGameObject* pObject = pInspector->GetTargetObject();

			if (nullptr == pObject)
			{
				ImGui::EndMenu();
				return;
			}

			pObject->AddComponent(new CTransform);
		}

		if (ImGui::MenuItem("Collider2D"))
		{
			Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
			CGameObject* pObject = pInspector->GetTargetObject();

			if (nullptr == pObject)
			{
				ImGui::EndMenu();
				return;
			}

			pObject->AddComponent(new CCollider2D);
		}

		if (ImGui::MenuItem("Animator2D"))
		{
			Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
			CGameObject* pObject = pInspector->GetTargetObject();

			if (nullptr == pObject)
			{
				ImGui::EndMenu();
				return;
			}

			pObject->AddComponent(new CAnimator2D);
		}

		if (ImGui::MenuItem("Rigidbody"))
		{
			Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
			CGameObject* pObject = pInspector->GetTargetObject();

			if (nullptr == pObject)
			{
				ImGui::EndMenu();
				return;
			}

			pObject->AddComponent(new CRigidbody);
		}

		if (ImGui::MenuItem("Camera"))
		{
			Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
			CGameObject* pObject = pInspector->GetTargetObject();

			if (nullptr == pObject)
			{
				ImGui::EndMenu();
				return;
			}

			pObject->AddComponent(new CCamera);
		}

		if (ImGui::MenuItem("Light2D"))
		{
			Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
			CGameObject* pObject = pInspector->GetTargetObject();

			if (nullptr == pObject)
			{
				ImGui::EndMenu();
				return;
			}

			pObject->AddComponent(new CLight2D);
		}

		if (ImGui::MenuItem("MeshRender"))
		{
			Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
			CGameObject* pObject = pInspector->GetTargetObject();

			if (nullptr == pObject)
			{
				ImGui::EndMenu();
				return;
			}

			pObject->AddComponent(new CMeshRender);
		}

		if (ImGui::MenuItem("TileMap"))
		{
			Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
			CGameObject* pObject = pInspector->GetTargetObject();

			if (nullptr == pObject)
			{
				ImGui::EndMenu();
				return;
			}

			pObject->AddComponent(new CTileMap);
		}

		ImGui::EndMenu();
	}
}

void MenuUI::AddScript()
{
	if (ImGui::BeginMenu("Add Script"))
	{
		vector<wstring> vecScriptsName;
		CScriptMgr::GetScriptInfo(vecScriptsName);

		for (size_t i = 0; i < vecScriptsName.size(); ++i)
		{
			if (ImGui::MenuItem(string(vecScriptsName[i].begin(), vecScriptsName[i].end()).c_str()))
			{
				Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");

				CGameObject* pObject = pInspector->GetTargetObject();

				if (nullptr != pObject)
				{
					CScript* pScript = CScriptMgr::GetScript(vecScriptsName[i]);
					pObject->AddComponent(pScript);
				}
			}	
		}

		ImGui::EndMenu();
	}
}

void MenuUI::CreateAnimation()
{
	CEditorMgr::GetInst()->FindEditorUI("Input Animation Name")->SetActive(true);
}

wstring MenuUI::GetAssetKey(ASSET_TYPE _Type, const wstring& _strKey)
{
	wstring strKey;

	switch (_Type)
	{
	case ASSET_TYPE::MATERIAL:
	{
		strKey = wstring(L"material\\" + _strKey + L" %d.mtrl");
	}
		break;
	case ASSET_TYPE::PREFAB:
		strKey = wstring(L"prefab\\" + _strKey + L" %d.pref");
		break;
	case ASSET_TYPE::SPRITE:
		strKey = wstring(L"sprite\\" + _strKey + L" %d.sprite");
		break;
	case ASSET_TYPE::ANIMATION:
		strKey = wstring(L"flipbook\\" + _strKey + L" %d.flip");
		break;
	default:
		assert(nullptr);
		break;
	}

	wchar_t szKey[255] = {};
	wstring FilePath = CPathMgr::GetInst()->GetContentPath();

	for (UINT i = 0; i < 0xffffffff; ++i)
	{
		swprintf_s(szKey, 255, strKey.c_str(), i);
		
		if (false == std::filesystem::exists(FilePath + szKey))
		{
			break;
		}
	}

	return szKey;
}