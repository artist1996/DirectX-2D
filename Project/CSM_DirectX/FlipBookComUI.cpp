#include "pch.h"
#include "FlipBookComUI.h"
#include "CEditorMgr.h"

#include <Engine/CGameObject.h>
#include <Engine/CAssetMgr.h>
#include <Engine/CSprite.h>
#include <Engine/CAnimation.h>
#include <Engine/CAnimator2D.h>

#include "ListUI.h"
#include "TreeUI.h"

FlipBookComUI::FlipBookComUI()
	: ComponentUI(COMPONENT_TYPE::ANIMATOR2D)
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

	CAnimator2D* pAnimator2D = pObject->Animator2D();
		
	if ((int)pAnimator2D->GetAnimationsSize() <= m_Idx)
	{
		m_Idx = (int)pAnimator2D->GetAnimationsSize() - 1;
	}

	if (m_Idx <= 0)
		m_Idx = 0;

	Ptr<CAnimation> pAnimation = pAnimator2D->GetCurAnimation();

	ImGui::Text("Cur Animation");
	ImGui::SameLine(100);
	string strName;
	if (nullptr != pAnimation)
		strName = string(pAnimation->GetKey().begin(), pAnimation->GetKey().end());
	else
		strName = "";

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

			if (ASSET_TYPE::ANIMATION == pAsset->GetAssetType())
			{
				vector<Ptr<CAnimation>> pAnimation = pAnimator2D->GetAnimations();

				if (0 == pAnimation.size())
				{
					pAnimator2D->AddAnimation(0, (CAnimation*)pAsset.Get());
				}
				else
				{
					//for (size_t i = 0; i < pAnimation.size(); ++i)
					//{
					//	if (nullptr != pAnimation[i])
					//		continue;
					//	else
					//	{
					//		pFlipBookCom->AddFlipBook(i + 1, (CFlipBook*)pAsset.Get());
					//		break;
					//	}
					//}
					pAnimator2D->AddAnimation(pAnimation.size(), (CAnimation*)pAsset.Get());
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
		
		vector<string> vecAnimationNames;

		for (size_t i = 0; i < pAnimator2D->GetAnimations().size(); ++i)
		{
			if (nullptr == pAnimator2D->GetAnimations()[i])
				continue;

			vecAnimationNames.push_back(string(pAnimator2D->GetAnimations()[i]->GetKey().begin(), pAnimator2D->GetAnimations()[i]->GetKey().end()));
		}
		
		pList->AddList(vecAnimationNames);
		pList->SetActive(true);
	}

	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	// Cur Sprite
	Ptr<CSprite> pSprite = pAnimator2D->GetCurSprite();

	if (nullptr == pSprite)
		return;

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
	int CurIndex = pAnimator2D->GetCurFrameIndex();
	
	ImGui::Text("Frame Index");
	ImGui::SameLine(100);
	ImGui::DragInt("##FrameIndex", &CurIndex);
	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	float FPS = pAnimator2D->GetFPS();

	ImGui::Text("FPS");
	ImGui::SameLine(100);
	ImGui::DragFloat("##Animation FPS", &FPS);
	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	pAnimator2D->SetFPS(FPS);


	SetChildSize(ImVec2(0.f, (float)m_UIHeight));
}

void FlipBookComUI::SelectFlipBook(DWORD_PTR _ListUI)
{
	ListUI* pList = (ListUI*)_ListUI;
	string strName = pList->GetSelectName();
	wstring strFlipBookName = wstring(strName.begin(), strName.end());
	Ptr<CAnimation> pFlipBook = CAssetMgr::GetInst()->FindAsset<CAnimation>(strFlipBookName);

	assert(pFlipBook.Get());
	CAnimator2D* pFlipBookCom = GetTargetObject()->Animator2D();
	pFlipBookCom->SetCurAnimation(pFlipBook);
	pFlipBookCom->Reset();
}