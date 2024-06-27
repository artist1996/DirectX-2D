#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CMeshRender.h>
#include <Engine/CMesh.h>
#include <Engine/CMaterial.h>

#include "CEditorMgr.h"
#include "ListUI.h"

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
	ImGui::SameLine();

	if (ImGui::Button("##MeshBtn", ImVec2(18.f, 18.f)))
	{
		// ListUI 활성화
		ListUI* pList = (ListUI*)CEditorMgr::GetInst()->FindEditorUI("List");
		pList->SetName("Mesh");
		pList->AddDelegate(this, (DELEGATE_1)&MeshRenderUI::SelectMesh);

		// AssetMgr 로 부터 Mesh Key 값 들고오기
		vector<string> vecMeshNames;
		CAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::MESH, vecMeshNames);
		pList->AddList(vecMeshNames);
		pList->SetActive(true);
	}

	Ptr<CMaterial> pMtrl = pMeshRender->GetMaterial();
	string strMaterialName = string(pMtrl->GetKey().begin(), pMtrl->GetKey().end());

	ImGui::Text("Material");
	ImGui::SameLine(100);
	ImGui::InputText("##MaterialKey", (char*)strMaterialName.c_str(), ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();

	if (ImGui::Button("##MaterialBtn", ImVec2(18.f, 18.f)))
	{
		// ListUI 활성화
		ListUI* pList = (ListUI*)CEditorMgr::GetInst()->FindEditorUI("List");
		pList->SetName("Material");
		pList->AddDelegate(this, (DELEGATE_1)&MeshRenderUI::SelectMaterial);

		// AssetMgr 로 부터 Material Key 값 들고오기
		vector<string> vecMtrlNames;
		CAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::MATERIAL, vecMtrlNames);
		pList->AddList(vecMtrlNames);
		pList->SetActive(true);
	}
}

void MeshRenderUI::SelectMesh(DWORD_PTR _ListUI)
{
	ListUI* pList = (ListUI*)_ListUI;
	string strName = pList->GetSelectName();
	wstring strMeshName = wstring(strName.begin(), strName.end());

	Ptr<CMesh> pMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(strMeshName);

	assert(pMesh.Get());

	CMeshRender* pMeshRender = GetTargetObject()->MeshRender();
	pMeshRender->SetMesh(pMesh);
}

void MeshRenderUI::SelectMaterial(DWORD_PTR _ListUI)
{
	ListUI* pList = (ListUI*)_ListUI;
	string strName = pList->GetSelectName();
	wstring strMtrlName = wstring(strName.begin(), strName.end());
	Ptr<CMaterial> pMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(strMtrlName);

	assert(pMtrl.Get());

	CMeshRender* pMeshRender = GetTargetObject()->MeshRender();
	pMeshRender->SetMaterial(pMtrl);
}
