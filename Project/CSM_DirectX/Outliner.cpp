#include "pch.h"
#include "Outliner.h"

#include "CEditorMgr.h"
#include "Inspector.h"
#include "TreeUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>


Outliner::Outliner()
	: m_Tree(nullptr)
{
	m_Tree = new TreeUI;
	m_Tree->SetName("OutlinerTree");
	AddChild(m_Tree);

	m_Tree->SetShowRoot(false);
	m_Tree->AddClickedDelegate(this, (DELEGATE_1)&Outliner::GameObjectClicked);

	RenewLevel();
}

Outliner::~Outliner()
{
}

void Outliner::Update()
{
	
}

void Outliner::RenewLevel()
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	if (nullptr == pLevel)
		return;

	TreeNode* pRootNode = m_Tree->AddNode(nullptr, "Root");

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pLevel->GetLayer(i);

		const vector<CGameObject*>& vecObjects = pLayer->GetParentObjects();

		for (size_t i = 0; i < vecObjects.size(); ++i)
		{
			AddGameObject(pRootNode, vecObjects[i]);
		}
	}
}

void Outliner::GameObjectClicked(DWORD_PTR _Param)
{
	TreeNode* pNode = (TreeNode*)_Param;
	CGameObject* pObject = (CGameObject*)pNode->GetData();

	if (nullptr == pObject)
		return;
	
	Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
	
	pInspector->SetTargetObject(pObject);
	ImGui::SetWindowFocus(nullptr);
}

void Outliner::AddGameObject(TreeNode* _Node, CGameObject* _Object)
{
	string strName = string(_Object->GetName().begin(), _Object->GetName().end());

	TreeNode* pObjectNode = m_Tree->AddNode(_Node, strName.c_str(), (DWORD_PTR)_Object);

	const vector<CGameObject*>& vecChild = _Object->GetChildren();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddGameObject(pObjectNode, vecChild[i]);
	}
}
