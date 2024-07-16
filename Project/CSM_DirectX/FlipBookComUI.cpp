#include "pch.h"
#include "FlipBookComUI.h"
#include "CEditorMgr.h"

#include <Engine/CGameObject.h>
#include <Engine/CAssetMgr.h>
#include <Engine/CSprite.h>
#include <Engine/CFlipBook.h>
#include <Engine/CFlipBookComponent.h>

#include "ListUI.h"

FlipBookComUI::FlipBookComUI()
	: ComponentUI(COMPONENT_TYPE::FLIPBOOKCOMPONENT)
{
}

FlipBookComUI::~FlipBookComUI()
{
}

void FlipBookComUI::Update()
{
	Title();

	CGameObject* pObject = GetTargetObject();

	CFlipBookComponent* pFlipBookCom = pObject->FlipBookComponent();

	static int Idx = 0;

	if ((int)pFlipBookCom->GetFlipBookSize() <= Idx)
	{
		Idx = (int)pFlipBookCom->GetFlipBookSize() - 1;
	}

	if (Idx <= 0)
		Idx = 0;

	Ptr<CFlipBook> pFlipBook = pFlipBookCom->GetCurFlipBook();
		
	ImGui::Text("Cur FlipBook");
	ImGui::SameLine(100);
	string strName = string(pFlipBook->GetKey().begin(), pFlipBook->GetKey().end());
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputText("##CurFlipBookName", (char*)strName.c_str(), strName.length(), ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	
	if (ImGui::Button("##CurFlipBookBtn", ImVec2(20.f,20.f)))
	{
		// ListUI 활성화
		ListUI* pList = (ListUI*)CEditorMgr::GetInst()->FindEditorUI("List");
		pList->SetName("FlipBook");
		pList->AddDelegate(this, (DELEGATE_1)&FlipBookComUI::SelectFlipBook);

		// AssetMgr 로 부터 Mesh Key 값 들고오기
		vector<string> vecFlipBookNames;
		CAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::FLIPBOOK, vecFlipBookNames);
		pList->AddList(vecFlipBookNames);
		pList->SetActive(true);
	}

	// Cur Sprite
	Ptr<CSprite> pSprite = pFlipBookCom->GetCurSprite();
	ImGui::Text("Cur Sprite");
	ImGui::SameLine(100);

	// Cur Sprite Name
	strName = string(pSprite->GetKey().begin(), pSprite->GetKey().end());
	ImGui::InputText("##CurSprite Name", (char*)strName.c_str(), strName.length(), ImGuiInputTextFlags_ReadOnly);

	// Cur Sprite Image
	ImVec2 uv_min = ImVec2(pSprite->GetLeftTopUV().x, pSprite->GetLeftTopUV().y);
	ImVec2 uv_max = ImVec2(uv_min.x + pSprite->GetSliceUV().x, uv_min.y + pSprite->GetSliceUV().y);

	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

	ImGui::Image(pSprite->GetAtlasTexture()->GetSRV().Get(), ImVec2(150.f, 150.f), uv_min, uv_max, tint_col, border_col);

	// Cur Frame Index
	int CurIndex = pFlipBookCom->GetCurFrameIndex();
	
	ImGui::Text("Frame Index");
	ImGui::SameLine(100);
	ImGui::DragInt("##FrameIndex", &CurIndex);
}

void FlipBookComUI::SelectFlipBook(DWORD_PTR _ListUI)
{
	ListUI* pList = (ListUI*)_ListUI;
	string strName = pList->GetSelectName();
	wstring strFlipBookName = wstring(strName.begin(), strName.end());
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(strFlipBookName);

	assert(pFlipBook.Get());

	CFlipBookComponent* pFlipBookCom = GetTargetObject()->FlipBookComponent();
	pFlipBookCom->SetCurFlipBook(pFlipBook);
}
