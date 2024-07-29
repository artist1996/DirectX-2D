#include "pch.h"
#include "TE_Detail.h"

#include <Engine/CAssetMgr.h>

#include "CEditorMgr.h"
#include "TreeUI.h"
#include "ListUI.h"

#include "TE_TextureView.h"
#include "TE_Renderer.h"

TE_Detail::TE_Detail()
{
}

TE_Detail::~TE_Detail()
{
}

void TE_Detail::Init()
{

}

void TE_Detail::Update()
{
	if (!IsActive())
		return;

	Texture();
}

void TE_Detail::Texture()
{
	string strKey;

	ImTextureID TexID = nullptr;

	if (nullptr != GetTexture())
		strKey = string(GetTexture()->GetKey().begin(), GetTexture()->GetKey().end());
		
	ImGui::Text("Name");
	ImGui::SameLine();
	ImGui::InputText("##TEDetailTexName", (char*)strKey.c_str(), strKey.length(), ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();
			if (ASSET_TYPE::TEXTURE == pAsset->GetAssetType())
			{
				SetTexture((CTexture*)pAsset.Get());
				GetTextureView()->SetTexture((CTexture*)pAsset.Get());
				GetRenderer()->SetTexture((CTexture*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##AtlasTexBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)CEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Texture");
		vector<string> vecTexNames;
		CAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::TEXTURE, vecTexNames);
		pListUI->AddList(vecTexNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&TE_Detail::SelectTexture);
		pListUI->SetActive(true);
	}
}

void TE_Detail::SelectTexture(DWORD_PTR _Param)
{
	CTexture* pTexture = (CTexture*)_Param;
	SetTexture(pTexture);
	GetTextureView()->SetTexture(pTexture);
	GetRenderer()->SetTexture(pTexture);
}
