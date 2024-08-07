#include "pch.h"
#include "PrefabUI.h"

#include <Engine/CPathMgr.h>
#include <Engine/CGameObject.h>

#include "CEditorMgr.h"
#include "EditorUI.h"
#include "Inspector.h"
#include "Content.h"

#include "TreeUI.h"

PrefabUI::PrefabUI()
	: AssetUI(ASSET_TYPE::PREFAB)
	, m_Idx(0)
{
}

PrefabUI::~PrefabUI()
{
}

void PrefabUI::Update()
{
	Title();

	Ptr<CPrefab> pPrefab = (CPrefab*)GetAsset().Get();
	CGameObject* pProtoObject = pPrefab->GetProtoObject();

	string strName;
	if (nullptr == pProtoObject)
		strName = "";
	else
		strName = string(pProtoObject->GetName().begin(), pProtoObject->GetName().end());

	ImGui::Text("Name");
	ImGui::SameLine();
	ImGui::InputText("##ProtoObjectName", (char*)strName.c_str(), 255, ImGuiInputTextFlags_ReadOnly);
	

	ImGui::Separator();

	if (ImGui::Button("Instantiate", ImVec2(100.f, 18.f)))
	{
		CGameObject* pCloneObj = pPrefab->Instantiate();

		CreateObject(pCloneObj, 0);
	}
}