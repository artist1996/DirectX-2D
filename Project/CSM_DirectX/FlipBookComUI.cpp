#include "pch.h"
#include "FlipBookComUI.h"
#include "CEditorMgr.h"

#include <Engine/CGameObject.h>
#include <Engine/CAssetMgr.h>
#include <Engine/CSprite.h>
#include <Engine/CFlipBook.h>
#include <Engine/CFlipBookComponent.h>

#include "ListUI.h"
#include "TreeUI.h"

FlipBookComUI::FlipBookComUI()
	: ComponentUI(COMPONENT_TYPE::FLIPBOOKCOMPONENT)
	, m_UIHeight(0)
	, m_Idx(0)
	, m_AddIdx(0)
{
}

FlipBookComUI::~FlipBookComUI()
{
}

void FlipBookComUI::Update()
{
	m_UIHeight = 0;
	Title();

	m_UIHeight += (int)ImGui::GetItemRectSize().y;
	CGameObject* pObject = GetTargetObject();

	CFlipBookComponent* pFlipBookCom = pObject->FlipBookComponent();
		
	if ((int)pFlipBookCom->GetFlipBookSize() <= m_Idx)
	{
		m_Idx = (int)pFlipBookCom->GetFlipBookSize() - 1;
	}

	if (m_Idx <= 0)
		m_Idx = 0;

	Ptr<CFlipBook> pFlipBook = pFlipBookCom->GetCurFlipBook();
		
	ImGui::Text("Cur FlipBook");
	ImGui::SameLine(100);
	string strName = string(pFlipBook->GetKey().begin(), pFlipBook->GetKey().end());
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputText("##CurFlipBookName", (char*)strName.c_str(), strName.length(), ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	m_UIHeight += (int)ImGui::GetItemRectSize().y;
	
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("ContentTree");

		if (Payload)
		{
			TreeNode* pNode = *((TreeNode**)Payload->Data);
			Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();

			if (ASSET_TYPE::FLIPBOOK == pAsset->GetAssetType())
			{
				vector<Ptr<CFlipBook>> pAnimation = pFlipBookCom->GetFlipBook();
				for (size_t i = 0; i < pAnimation.size(); ++i)
				{
					if (nullptr != pAnimation[i])
						continue;
					else
					{
						pFlipBookCom->AddFlipBook(i, (CFlipBook*)pAsset.Get());
						break;
					}
				}
			}
		}

		ImGui::EndDragDropTarget();
	}

	if (ImGui::Button("##CurFlipBookBtn", ImVec2(20.f,20.f)))
	{
		// ListUI 활성화
		ListUI* pList = (ListUI*)CEditorMgr::GetInst()->FindEditorUI("List");
		pList->SetName("FlipBook");
		pList->AddDelegate(this, (DELEGATE_1)&FlipBookComUI::SelectFlipBook);

		// AssetMgr 로 부터 Mesh Key 값 들고오기
		
		vector<string> vecFlipBookNames;

		for (size_t i = 0; i < pFlipBookCom->GetFlipBook().size(); ++i)
		{
			if (nullptr == pFlipBookCom->GetFlipBook()[i])
				continue;

			vecFlipBookNames.push_back(string(pFlipBookCom->GetFlipBook()[i]->GetKey().begin(), pFlipBookCom->GetFlipBook()[i]->GetKey().end()));
		}
		
		pList->AddList(vecFlipBookNames);
		pList->SetActive(true);
	}

	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	// Cur Sprite
	Ptr<CSprite> pSprite = pFlipBookCom->GetCurSprite();
	ImGui::Text("Cur Sprite");
	ImGui::SameLine(100);
	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	// Cur Sprite Name
	strName = string(pSprite->GetKey().begin(), pSprite->GetKey().end());
	ImGui::InputText("##CurSprite Name", (char*)strName.c_str(), strName.length(), ImGuiInputTextFlags_ReadOnly);
	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	// Cur Sprite Image
	ImVec2 uv_min = ImVec2(pSprite->GetLeftTopUV().x, pSprite->GetLeftTopUV().y);
	ImVec2 uv_max = ImVec2(uv_min.x + pSprite->GetSliceUV().x, uv_min.y + pSprite->GetSliceUV().y);

	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

	ImGui::Image(pSprite->GetAtlasTexture()->GetSRV().Get(), ImVec2(150.f, 150.f), uv_min, uv_max, tint_col, border_col);
	m_UIHeight += (int)ImGui::GetItemRectSize().y;
	// Cur Frame Index
	int CurIndex = pFlipBookCom->GetCurFrameIndex();
	
	ImGui::Text("Frame Index");
	ImGui::SameLine(100);
	ImGui::DragInt("##FrameIndex", &CurIndex);
	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	SetChildSize(ImVec2(0.f, (float)m_UIHeight));
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
	pFlipBookCom->Reset();
}