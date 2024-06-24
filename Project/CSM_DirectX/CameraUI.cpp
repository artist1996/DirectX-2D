#include "pch.h"
#include "CameraUI.h"

#include <Engine/CCamera.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

CameraUI::CameraUI()
	: ComponentUI(COMPONENT_TYPE::CAMERA)
    , m_ShowLayerCheck(false)
{
}

CameraUI::~CameraUI()
{
}

void CameraUI::Update()
{
    Title();
    // m_Priority; (º¸·ù)
    
    // m_LayerCheck;
    LayerCheck();

    // m_ProjType;
    
    // m_Width;
    // m_Height;
    // m_Far;       
    
    // m_FOV;       

}

void CameraUI::LayerCheck()
{
    ImGui::Text("Layer Check");
    ImGui::SameLine(100);
    if (ImGui::Button("Show##LayerCheckBtn", ImVec2(50.f, 18.f)))
    {
        m_ShowLayerCheck ? m_ShowLayerCheck = false : m_ShowLayerCheck = true;
    }

    if (!m_ShowLayerCheck)
        return;


    CCamera* pCam = GetTargetObject()->Camera();

    bool bLayer[32] = {};
    for (int i = 0; i < 32; ++i)
    {
        bLayer[i] = pCam->GetLayerCheck(i);
    }

    int ChangedIdx = -1;
    if (ImGui::BeginTable("##LayerCheckTable", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
    {
        for (int i = 0; i < 32; i++)
        {
            char label[32];
            sprintf_s(label, "Layer %d", i);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (ImGui::Selectable(label, &bLayer[i], ImGuiSelectableFlags_SpanAllColumns))
            {
                ChangedIdx = i;
            }

            wstring wlayerName = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(i)->GetName();
            string layerName(wlayerName.begin(), wlayerName.end());
            ImGui::TableNextColumn();
            ImGui::Text(layerName.c_str());
        }
        ImGui::EndTable();
    }

    if (ChangedIdx != -1)
    {
        pCam->SetLayer(ChangedIdx, bLayer[ChangedIdx]);
    }
}