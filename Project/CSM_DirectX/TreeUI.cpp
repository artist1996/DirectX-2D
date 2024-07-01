#include "pch.h"
#include "TreeUI.h"

// ========
// TreeNode
// ========

TreeNode::TreeNode()
	: m_ParentNode(nullptr)
{
}

TreeNode::~TreeNode()
{
	Delete_Vec(m_vecChildNode);
}

void TreeNode::AddChildNode(TreeNode* _Node)
{
	m_vecChildNode.push_back(_Node);
	_Node->m_ParentNode = this;
}

void TreeNode::Update()
{
	if (ImGui::TreeNodeEx(m_strName.c_str()))
	{
		for (size_t i = 0; i < m_vecChildNode.size(); ++i)
		{
			m_vecChildNode[i]->Update();
		}

		ImGui::TreePop();
	}
}







// ======
// TreeUI
// ======

TreeUI::TreeUI()
	: m_Root(nullptr)
{
}

TreeUI::~TreeUI()
{
	if (nullptr != m_Root)
		delete m_Root;
}

void TreeUI::Update()
{
	if (nullptr == m_Root)
		return;

	m_Root->Update();
}

void TreeUI::AddNode(const string& _strName)
{
	TreeNode* pNode = new TreeNode;

	if (nullptr == m_Root)
	{
		m_Root = pNode;
	}

	pNode->SetName(_strName);
}
