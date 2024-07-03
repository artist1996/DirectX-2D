#include "pch.h"
#include "Inspector.h"
#include "ImGui/imgui.h"

#include "ComponentUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

#include <Engine/CGameObject.h>

#include "AssetUI.h"

Inspector::Inspector()
	: m_TargetObject(nullptr)
	, m_TargetAsset(nullptr)
	, m_arrComUI{}
	, m_arrAssetUI{}
{
}

Inspector::~Inspector()
{
}

void Inspector::Update()
{
	if (nullptr == m_TargetObject)
		return;

	// Target Object Name
	string strObjectName = string(m_TargetObject->GetName().begin(), m_TargetObject->GetName().end());
	ImGui::Text("Object Name");
	ImGui::SameLine(100);
	ImGui::InputText("##ObjectName", (char*)strObjectName.c_str(), strObjectName.length(), ImGuiInputTextFlags_ReadOnly);
	
	// Target Object Layer
	int LayerIdx = m_TargetObject->GetLayerIdx();
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pCurLevel->GetLayer(LayerIdx);
	string strLayerName = string(pLayer->GetName().begin(), pLayer->GetName().end());

	char szBuff[50] = {};
	if (strLayerName.empty())
	{
		sprintf_s(szBuff, 50, "%d : %s", LayerIdx, "None");
	}
	else
	{
		sprintf_s(szBuff, 50, "%d : %s", LayerIdx, strLayerName.c_str());
	}
	ImGui::Text("Layer");
	ImGui::SameLine(100);
	ImGui::InputText("##LayerName", szBuff, strlen(szBuff), ImGuiInputTextFlags_ReadOnly);

	int Idx = m_TargetObject->GetLayerIdx();

	ImGui::Text("Change Layer");
	ImGui::SameLine(100);

	if (ImGui::InputInt("##ChangeLayer", &Idx))
	{
		if (-1 == Idx)
			Idx = 0;
		if (Idx >= 31)
			Idx = 31;

		m_TargetObject->ChangeLayer(m_TargetObject, Idx);
	}

}

void Inspector::SetTargetObject(CGameObject* _Target)
{
	m_TargetObject = _Target;
	
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrComUI[i])
			continue;

		m_arrComUI[i]->SetTargetObject(_Target);
	}

	m_TargetAsset = nullptr;

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->SetAsset(nullptr);
	}
}

void Inspector::SetTargetAsset(Ptr<CAsset> _Asset)
{
	if (nullptr == _Asset)
		return;

	SetTargetObject(nullptr);

	m_TargetAsset = _Asset;
	
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->SetAsset(m_TargetAsset);
	}
}
