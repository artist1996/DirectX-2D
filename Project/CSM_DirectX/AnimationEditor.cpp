#include "pch.h"
#include "AnimationEditor.h"

#include <Engine/CPathMgr.h>
#include <Engine/CAssetMgr.h>
#include <Engine/CTexture.h>


AnimationEditor::AnimationEditor()
	: m_Animation(nullptr)
	, m_TargetSprite(nullptr)
	, m_strTexName{}
	, m_strSpriteName{}
	, m_DrawingRect(false)
{
}

AnimationEditor::~AnimationEditor()
{
}

void AnimationEditor::Update()
{
	LoadTexture();

	ShowTextureImage();

	InputSpriteName();

	SpriteInfo();

	EditSprite();
}

void AnimationEditor::ClearEditor()
{
	m_Texture = nullptr;
	m_Animation = nullptr;
	m_TargetSprite = nullptr;
	m_strTexName.clear();	
	m_strSpriteName.clear();

	m_LT = ImVec2(0.f,0.f);
	m_RB = ImVec2(0.f, 0.f);
	m_StartPos = ImVec2(0.f, 0.f);
	m_LeftTopPos = ImVec2(0.f, 0.f);
	m_SlicePos = ImVec2(0.f, 0.f);
	m_DrawingRect = false;
}

void AnimationEditor::Deactivate()
{
	SetActive(false);
	ClearEditor();
}

void AnimationEditor::LoadTexture()
{
	ImGui::Text("Texture");
	ImGui::SameLine(100);
	ImGui::SetNextItemWidth(180.f);
	ImGui::InputText("##LoadTextureName", (char*)m_strTexName.c_str(), 255, ImGuiInputTextFlags_ReadOnly);

	ImGui::SameLine(300);
	if (ImGui::Button("Load Texture", ImVec2(100.f, 20.f)))
	{
		OpenLoadTexture();
	}
}

void AnimationEditor::ShowTextureImage()
{
	if (nullptr == m_Texture)
		return;
	
	// Texture Image
	ImVec2 uv_min = ImVec2(0.0f, 0.0f);
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);

	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

	ImTextureID TexID = nullptr;

	if (nullptr != m_Texture->GetSRV())
		TexID = m_Texture->GetSRV().Get();

	ImGui::Image(TexID, ImVec2(m_Texture->Width(), m_Texture->Height()), uv_min, uv_max, tint_col, border_col);

	ImVec2 Image_LT = ImGui::GetItemRectMin();
	ImVec2 Image_RB = ImGui::GetItemRectMax();

	ImDrawList* Draw_List = ImGui::GetWindowDrawList();

	if (ImGui::IsItemHovered())
	{
		ImVec2 CurMousePos = ImGui::GetMousePos();

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			m_StartPos = CurMousePos;
		}

		if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
		{
			m_LT.x = m_StartPos.x - Image_LT.x;
			m_LT.y = m_StartPos.y - Image_LT.y;

			m_RB.x = abs(CurMousePos.x - Image_LT.x); // Update the right-bottom corner
			m_RB.y = abs(CurMousePos.y - Image_LT.y);

			m_DrawingRect = true;

			m_LeftTopPos = ImVec2(Image_LT.x + m_LT.x, Image_LT.y + m_LT.y);
			m_SlicePos = ImVec2(Image_LT.x + m_RB.x, Image_LT.y + m_RB.y);
			Draw_List->AddRect(m_LeftTopPos, m_SlicePos, IM_COL32(0, 255, 0, 255));
		}

		if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
		{
			Vec2 SliceSize = Vec2(m_RB.x - m_LT.x, m_RB.y - m_LT.y);
			m_TargetSprite->SetLeftTopUV(Vec2(m_LT.x, m_LT.y));
			m_TargetSprite->SetSliceUV(SliceSize);
		}
	}

	Draw_List->AddRect(m_LeftTopPos, m_SlicePos, IM_COL32(0, 255, 0, 255));
}

void AnimationEditor::OpenLoadTexture()
{
	wchar_t szSelect[256] = {};
	wchar_t szRelativePath[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szSelect;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szSelect);
	ofn.lpstrFilter = L"";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;

	// 탐색창 초기 위치 지정
	wstring strInitPath = CPathMgr::GetInst()->GetContentPath();
	strInitPath += L"\\content\\texture";
	ofn.lpstrInitialDir = strInitPath.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{	
		wstring FilePath = CPathMgr::GetInst()->GetContentPath();

		std::filesystem::path RelativePath = std::filesystem::relative(szSelect, FilePath);

		if (m_Texture.Get())
			m_Texture = nullptr;

		m_Texture = CAssetMgr::GetInst()->Load<CTexture>(RelativePath.c_str(), RelativePath.c_str());
		m_strTexName = string(m_Texture->GetKey().begin(), m_Texture->GetKey().end());
		m_TargetSprite->Create(m_Texture, Vec2(0.f, 0.f), Vec2(m_Texture->Width(), m_Texture->Height()));
	}
}

void AnimationEditor::EditSprite()
{
	if (ImGui::Button("Edit", ImVec2(50.f, 40.f)))
	{
		if (nullptr == m_TargetSprite->GetAtlasTexture())
			return;

		CAssetMgr::GetInst()->AddAsset(wstring(m_strSpriteName.begin(), m_strSpriteName.end()), m_TargetSprite);
		m_Animation->AddSprite(m_TargetSprite);
		Deactivate();
	}
}

void AnimationEditor::InputSpriteName()
{
	char szName[255] = {};
	ImGui::Text("Input Name");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(200.f);
	if (ImGui::InputText("##InputSpriteName", szName, 255))
	{
		m_strSpriteName = szName;
	}
}

void AnimationEditor::SpriteInfo()
{
	if (nullptr == m_TargetSprite->GetAtlasTexture())
		return;

	Vec2 vResolution = Vec2((float)m_TargetSprite->GetAtlasTexture()->Width(), (float)m_TargetSprite->GetAtlasTexture()->Height());
	Vec2 vLeftTop = vResolution * m_TargetSprite->GetLeftTopUV();
	Vec2 vSliceSize;
	if (Vec2(1.f, 1.f) == m_TargetSprite->GetSliceUV())
		vSliceSize = Vec2(0.f, 0.f);
	else
	    vSliceSize = vResolution * m_TargetSprite->GetSliceUV();

	ImGui::Text("LT");
	ImGui::SameLine(86);
	ImGui::DragFloat2("##SpriteLeftTopPos", vLeftTop);

	ImGui::Text("Slice Size");
	ImGui::SameLine();
	ImGui::DragFloat2("##SpriteSliceSize", vSliceSize);
}
