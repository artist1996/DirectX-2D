#include "pch.h"
#include "AnimationPopup.h"

#include "CEditorMgr.h"
#include <Engine/CAssetMgr.h>

AnimationPopup::AnimationPopup()
	: m_strName{}
	, m_strKey{}
{
	SetActive(false);
}

AnimationPopup::~AnimationPopup()
{
}

void AnimationPopup::Update()
{
	ImGui::SetWindowFocus();

	ImGui::Text("Name");
	ImGui::SameLine(50);
	ImGui::SetNextItemWidth(200.f);

	char szBuff[255] = {};

	if (ImGui::InputText("##InputName", szBuff, 255))
	{
		m_strName = szBuff;
	}

	if (ImGui::Button("OK", ImVec2(120, 0)))
	{
		m_strKey = wstring(m_strName.begin(), m_strName.end());

		Ptr<CFlipBook> pFlipBook = new CFlipBook;

		CAssetMgr::GetInst()->AddAsset(m_strKey.c_str(), pFlipBook);

		SetActive(false);
	}
	ImGui::SetItemDefaultFocus();
	ImGui::SameLine();

	if (ImGui::Button("Cancel", ImVec2(120, 0)))
	{
		ImGui::CloseCurrentPopup();
		AnimationEditor* pEditor = (AnimationEditor*)CEditorMgr::GetInst()->FindEditorUI("Animation Editor");
		pEditor->ClearEditor();
		pEditor->SetActive(false);
	}
	
}