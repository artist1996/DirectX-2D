#include "pch.h"
#include "AnimationUI.h"

#include <Engine/CAssetMgr.h>
#include "AnimationEditor.h"
#include "SpriteEditor.h"

AnimationUI::AnimationUI()
	: m_FlipBook(nullptr)
	, m_arrChild{}
{
	SetActive(false);
}

AnimationUI::~AnimationUI()
{
	
}

void AnimationUI::Update()
{
	//if (CAssetMgr::GetInst()->IsChanged())
	//	return;

	ImGui::Text("Input Name");
	ImGui::SameLine(100);
	ImGui::SetNextItemWidth(150.f);

	static char szBuff[255] = {};

	if (ImGui::InputText("##InputFlipBookName", szBuff, sizeof(szBuff)))
	{
		m_strName = szBuff;
	}

	ImGui::SameLine(280.f);
	if (ImGui::Button("Create", ImVec2(60.f, 20.f)))
	{
		Ptr<CFlipBook> pFlipBook = new CFlipBook;
		pFlipBook->SetName(wstring(m_strName.begin(), m_strName.end()));
		m_FlipBook = pFlipBook;
	}

	if (ImGui::Button("Edit", ImVec2(50.f, 50.f)))
	{
		CAssetMgr::GetInst()->AddAsset(wstring(m_strName.begin(), m_strName.end()), m_FlipBook);
	}

	if (ImGui::Button("Save", ImVec2(50.f, 50.f)))
	{
	}
}

void AnimationUI::Init()
{
	// SpriteUI
	AnimationEditor* pUI = new SpriteEditor;
	pUI->SetName("Sprite Editor");
	pUI->SetChildBorder(true);
	pUI->SetChildSize(ImVec2(0.f, 130.f));
	AddChild(pUI);

	m_arrChild[0] = pUI;
	//m_arrAnimChild[1] = new PreviewEditor;
}
