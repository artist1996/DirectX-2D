#include "pch.h"
#include "FlipBookUI.h"

#include "CEditorMgr.h"
#include "AnimationEditor.h"

FlipBookUI::FlipBookUI()
	: AssetUI(ASSET_TYPE::FLIPBOOK)
{
}

FlipBookUI::~FlipBookUI()
{
}

void FlipBookUI::Update()
{
	Title();

	Ptr<CFlipBook> pAnimation = (CFlipBook*)GetAsset().Get();

	int maxIdx = pAnimation->GetMaxFrameCount() - 1;
	static int Idx = 0;

	// Cur Sprite Image
	if (0 != pAnimation->GetMaxFrameCount())
	{
		ImGui::Text("Sprite");

		Ptr<CSprite> pSprite = pAnimation->GetSprite(Idx);

		ImVec2 uv_min = ImVec2(pSprite->GetLeftTopUV().x, pSprite->GetLeftTopUV().y);
		ImVec2 uv_max = ImVec2(uv_min.x + pSprite->GetSliceUV().x, uv_min.y + pSprite->GetSliceUV().y);

		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

		ImGui::Image(pSprite->GetAtlasTexture()->GetSRV().Get(), ImVec2(150.f, 150.f), uv_min, uv_max, tint_col, border_col);

		// Name
		ImGui::Text("Name");
		ImGui::SameLine(100);
		string strName = string(pAnimation->GetKey().begin(), pAnimation->GetKey().end());
		ImGui::InputText("##FlipBookName", (char*)strName.c_str(), strName.length(), ImGuiInputTextFlags_ReadOnly);

		// Index
		ImGui::Text("Index");
		ImGui::SameLine(100);
		ImGui::SliderInt("##Index", &Idx, 0, maxIdx);

		// Cur Sprite Info

		// LeftTop
		Vec2 vLeftTopUV = pSprite->GetLeftTopUV();
		Vec2 vResolution = Vec2((float)pSprite->GetAtlasTexture()->Width(), (float)pSprite->GetAtlasTexture()->Height());
		Vec2 vLeftTop = vResolution * vLeftTopUV;

		ImGui::Text("LeftTop");
		ImGui::SameLine(100);
		ImGui::InputFloat2("##LeftTop", (float*)&vLeftTop);

		// Slice
		Vec2 vSliceUV = pSprite->GetSliceUV();
		Vec2 vSlice = vResolution * vSliceUV;

		ImGui::Text("Slice");
		ImGui::SameLine(100);
		ImGui::InputFloat2("##Slice", (float*)&vSlice);

		// Offset
		Vec2 vOffsetUV = pSprite->GetOffsetUV();
		Vec2 vOffset = vResolution * vOffsetUV;

		ImGui::Text("Offset");
		ImGui::SameLine(100);
		ImGui::InputFloat2("##Offset", (float*)&vOffset);

		// Background
		Vec2 vBackgroundUV = pSprite->GetBackgroundUV();
		Vec2 vBackground = vResolution * vBackgroundUV;

		ImGui::Text("Background");
		ImGui::SameLine(100);
		ImGui::InputFloat2("##Background", (float*)&vBackground);

		pSprite->SetLeftTopUV(vLeftTop);
		pSprite->SetSliceUV(vSlice);
		pSprite->SetOffsetUV(vOffset);
		pSprite->SetBackgroundUV(vBackground);

		AddFrame();
	}

	else
	{
		ImGui::Text("Sprite");

		ImVec2 uv_min = ImVec2(0.f, 0.f);
		ImVec2 uv_max = ImVec2(1.f, 1.f);

		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

		ImTextureID TexID = nullptr;

		ImGui::Image(TexID, ImVec2(150.f, 150.f), uv_min, uv_max, tint_col, border_col);

		// Name
		ImGui::Text("Name");
		ImGui::SameLine(100);
		string strName = string(pAnimation->GetKey().begin(), pAnimation->GetKey().end());
		ImGui::InputText("##FlipBookName", (char*)strName.c_str(), strName.length(), ImGuiInputTextFlags_ReadOnly);

		AddFrame();
	}
}

void FlipBookUI::AddFrame()
{
	if (ImGui::Button("Add Frame", ImVec2(80.f, 20.f)))
	{
		AnimationEditor* pEditor = (AnimationEditor*)CEditorMgr::GetInst()->FindEditorUI("Animation Editor");
		
		Ptr<CSprite> pSprite = new CSprite;
		pEditor->SetTargetSprite(pSprite);
		pEditor->SetAnimation((CFlipBook*)GetAsset().Get());

		pEditor->SetActive(true);
	}
}
