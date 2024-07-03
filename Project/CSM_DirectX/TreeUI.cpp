#include "pch.h"
#include "TreeUI.h"

// ========
// TreeNode
// ========

TreeNode::TreeNode(UINT _ID)
	: m_Owner(nullptr)
	, m_ParentNode(nullptr)
	, m_ID(_ID)
	, m_Data(0)
	, m_Frame(false)
	, m_Selected(false)
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
	UINT Flags = ImGuiTreeNodeFlags_OpenOnDoubleClick
			   | ImGuiTreeNodeFlags_SpanAvailWidth
			   | ImGuiTreeNodeFlags_OpenOnArrow;
	
	if (m_Frame)	
		Flags |= ImGuiTreeNodeFlags_Framed;
	if (m_Selected)
		Flags |= ImGuiTreeNodeFlags_Selected;
	
	char szName[255] = {};
	
	if (m_vecChildNode.empty())
	{
		Flags |= ImGuiTreeNodeFlags_Leaf;
		if(m_Frame)
			sprintf_s(szName, "   %s##%d", m_strName.c_str(), m_ID);
		else
			sprintf_s(szName, "%s##%d", m_strName.c_str(), m_ID);
	}
	else
	{
		sprintf_s(szName, "%s##%d", m_strName.c_str(), m_ID);
	}

	if (ImGui::TreeNodeEx(szName, Flags))
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
			m_Owner->SetSelectedNode(this);

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
	, m_SelectedNode(nullptr)
	, m_NodeID(0)
	, m_ShowRoot(false)
{
}

TreeUI::~TreeUI()
{
	Clear();
}

void TreeUI::Update()
{
	if (nullptr == m_Root)
		return;

	if(m_ShowRoot)
		m_Root->Update();

	else
	{
		for (size_t i = 0; i < m_Root->m_vecChildNode.size(); ++i)
		{
			m_Root->m_vecChildNode[i]->Update();
		}
	}
}

TreeNode* TreeUI::AddNode(TreeNode* _Parent, const string& _strName, DWORD_PTR _Data)
{
	// Node ���� �� ID, Data ����
	TreeNode* pNode = new TreeNode(m_NodeID++);
	pNode->m_Owner = this;
	pNode->SetName(_strName);
	pNode->m_Data = _Data;
	
	// �θ� �������� ������ Root Node �� ����
	if (nullptr == _Parent)
	{
		assert(!m_Root);

		m_Root = pNode;
	}	
	// �װ� �ƴ϶�� �ش� �θ��� �ڽ����� ����
	else
	{
		_Parent->AddChildNode(pNode);
	}

	return pNode;
}

void TreeUI::SetSelectedNode(TreeNode* _Node)
{
	// ������ ���� ���¿��� Node�� ����
	if (nullptr != m_SelectedNode)
		m_SelectedNode->m_Selected = false;

	// ���ο� ��带 ���õ� ���� ����
	m_SelectedNode = _Node;

	// ���ο� ��带 ���õ� ���·� ���� �� �Լ������� ȣ��
	if (nullptr != m_SelectedNode)
	{
		m_SelectedNode->m_Selected = true;

		if (m_ClickedInst && m_ClickedFunc)
		{
			(m_ClickedInst->*m_ClickedFunc)((DWORD_PTR)m_SelectedNode);
		}
	}
}

void TreeUI::Clear()
{
	if (nullptr != m_Root)
	{
		delete m_Root;
		m_Root = nullptr;
	}
}