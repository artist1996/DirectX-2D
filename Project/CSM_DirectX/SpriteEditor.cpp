#include "pch.h"
#include "SpriteEditor.h"

#include "CEditorMgr.h"
#include "TreeUI.h"

SpriteEditor::SpriteEditor()
	: m_Tree(nullptr)
	, m_Active(false)
{
	SetActive(true);

	m_Tree = new TreeUI;
	m_Tree->SetName("Sprite Tree");
	AddChild(m_Tree);

	m_Tree->SetChildSize(ImVec2(150.f, 500.f));
	m_Tree->SetShowRoot(false);
	m_Tree->UseDrag(true);
	m_Tree->SetShowNameOnly(true);
}

SpriteEditor::~SpriteEditor()
{
}

void SpriteEditor::Update()
{
	Title();
	// Texture Load
	
	// Sprite Add
	ImGui::Text("Input Name");
	ImGui::SameLine(91);
	ImGui::SetNextItemWidth(150.f);

	static char szBuff[255] = {};
	if (ImGui::InputText("##Input Name", szBuff, sizeof(szBuff)))
	{
		m_strName = szBuff;
	}

	ImGui::SameLine(270);

	if (ImGui::Button("Add Frame", ImVec2(80.f, 20.f)))
	{
		Ptr<CSprite> pSprite = new CSprite;
		pSprite->SetName(wstring(m_strName.begin(), m_strName.end()));
		AnimationUI* pUI = (AnimationUI*)CEditorMgr::GetInst()->FindEditorUI("Animation Editor");
		Ptr<CFlipBook> pFlipBook = pUI->GetTargetFlipBook();

		if (nullptr == pFlipBook)
			return;

		pFlipBook->AddSprite(pSprite);
		SetTargetSprite(pSprite);
		m_Active = true;
		RenewTree();
	}
}

void SpriteEditor::RenewTree()
{
	m_Tree->Clear();
	TreeNode* pRoot = m_Tree->AddNode(nullptr, "Root");

	AnimationUI* pUI = (AnimationUI*)CEditorMgr::GetInst()->FindEditorUI("Animation Editor");

	Ptr<CFlipBook> pFlipBook = pUI->GetTargetFlipBook();

	if (nullptr == pFlipBook)
		return;

	for (size_t i = 0; i < pFlipBook->GetSize(); ++i)
	{
		Ptr<CSprite> pSprite = pFlipBook->GetSprite(i);
		string strName = string(pSprite->GetName().begin(), pSprite->GetName().end());
		TreeNode* pNode = m_Tree->AddNode(pRoot, strName, (DWORD_PTR)pSprite.Get());
	}	
}
