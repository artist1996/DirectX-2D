#include "pch.h"
#include "Inspector.h"
#include "ImGui/imgui.h"

#include "ComponentUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

#include <Engine/CGameObject.h>
#include "TransformUI.h"
#include "Collider2DUI.h"
#include "CameraUI.h"
#include "FlipBookComUI.h"
#include "MeshRenderUI.h"
#include "TileMapUI.h"
#include "ParticleSystemUI.h"
#include "Light2DUI.h"

Inspector::Inspector()
	: m_TargetObject(nullptr)
	, m_arrComUI{}
{
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new TransformUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]->SetName("TrasnformUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]->SetChildSize(ImVec2(0.f, 130.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]);

	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D] = new Light2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]->SetName("Light2DUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]->SetChildSize(ImVec2(0.f, 200.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]);

	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D] = new Collider2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->SetName("Collider2DUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->SetChildSize(ImVec2(0.f, 100.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]);

	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA] = new CameraUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]->SetName("CameraUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]->SetChildSize(ImVec2(0.f, 200.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]);

	m_arrComUI[(UINT)COMPONENT_TYPE::FLIPBOOKCOMPONENT] = new FlipBookComUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::FLIPBOOKCOMPONENT]->SetName("FlipBookComUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::FLIPBOOKCOMPONENT]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::FLIPBOOKCOMPONENT]->SetChildSize(ImVec2(0.f, 100.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::FLIPBOOKCOMPONENT]);

	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER] = new MeshRenderUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]->SetName("MeshRenderUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]->SetChildSize(ImVec2(0.f, 100.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]);

	m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP] = new TileMapUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP]->SetName("TileMapUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP]->SetChildSize(ImVec2(0.f, 100.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP]);

	m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLE_SYSTEM] = new ParticleSystemUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLE_SYSTEM]->SetName("ParticleSystemUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLE_SYSTEM]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLE_SYSTEM]->SetChildSize(ImVec2(0.f, 100.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLE_SYSTEM]);
}

Inspector::~Inspector()
{
}

void Inspector::Update()
{
	if (nullptr == m_TargetObject)
	{
		SetTargetObject(CLevelMgr::GetInst()->FindObjectByName(L"Player"));
		//SetTargetObject(CLevelMgr::GetInst()->FindObjectByName(L"MainCamera"));
		//SetTargetObject(CLevelMgr::GetInst()->FindObjectByName(L"Directional"));
		return;
	}

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
}
