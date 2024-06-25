#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine/CMeshRender.h>
#include <Engine/CMesh.h>
#include <Engine/CMaterial.h>

MeshRenderUI::MeshRenderUI()
	: ComponentUI(COMPONENT_TYPE::MESHRENDER)
{
}

MeshRenderUI::~MeshRenderUI()
{
}

void MeshRenderUI::Update()
{
	Title();

	CMeshRender* pMeshRender = GetTargetObject()->MeshRender();

	Ptr<CMesh> pMesh = pMeshRender->GetMesh();
	string strMeshName = string(pMesh->GetKey().begin(), pMesh->GetKey().end());

	ImGui::Text("Mesh");
	ImGui::SameLine(100);
	ImGui::InputText("##MeshKey", (char*)strMeshName.c_str(), ImGuiInputTextFlags_ReadOnly);

	Ptr<CMaterial> pMtrl = pMeshRender->GetMaterial();
	string strMaterialName = string(pMtrl->GetKey().begin(), pMtrl->GetKey().end());

	ImGui::Text("Material");
	ImGui::SameLine(100);
	ImGui::InputText("##MaterialKey", (char*)strMaterialName.c_str(), ImGuiInputTextFlags_ReadOnly);
}