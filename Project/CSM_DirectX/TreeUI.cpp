#include "pch.h"
#include "TreeUI.h"

#include <Engine/CKeyMgr.h>

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

	string strName = m_strName;

	// NameOnly
	if (m_Owner->IsShowNameOnly())
	{
		path Path = strName;
		strName = Path.stem().string();
	}

	if (ImGui::TreeNodeEx(strName.c_str(), Flags))
	{
		if (ImGui::IsItemHovered()
		 && ImGui::IsKeyDown(ImGuiKey_LeftShift)
		 && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		{
			if (m_Owner->GetSelectedNode())
			{
				m_Owner->SetDuplicateNode(this);
			}
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left) && !ImGui::IsKeyDown(ImGuiKey_LeftShift))
			m_Owner->SetSelectedNode(this);

		DragCheck();
		DropCheck();

		if (ImGui::BeginPopupContextItem())
		{
			// Popup ������ ��� ä����
			m_Owner->PopupMenu(this);
			// ��带 ��Ŭ�� �� ���õ� ������ ����
			m_Owner->SetSelectedNode(this);
		}

		for (size_t i = 0; i < m_vecChildNode.size(); ++i)
		{
			m_vecChildNode[i]->Update();
		}

		ImGui::TreePop();
	}
}

void TreeNode::EraseChild(TreeNode* _Node)
{
	vector<TreeNode*>::iterator iter = m_vecChildNode.begin();

	for (; iter != m_vecChildNode.end();)
	{
		if ((*iter) == _Node)
			iter = m_vecChildNode.erase(iter);
		else
			++iter;
	}
}

void TreeNode::DragCheck()
{
	if (m_Owner->IsDrag())
	{
		if (ImGui::BeginDragDropSource())
		{
			if (m_Owner->IsEmptyDuplicateNodes())
			{
				TreeNode* pDragNode = this;
				ImGui::SetDragDropPayload(m_Owner->GetName().c_str(), &pDragNode, sizeof(TreeNode*));
				ImGui::Text(m_strName.c_str());
				ImGui::EndDragDropSource();

				m_Owner->SetDragedNode(this);
			}

			else
			{
				const vector<TreeNode*>& vecDuplicateNodes = m_Owner->GetDuplicateNodes();

				ImGui::SetDragDropPayload(m_Owner->GetName().c_str(), vecDuplicateNodes.data(), vecDuplicateNodes.size() * sizeof(TreeNode*));
				ImGui::Text(m_strName.c_str());
				ImGui::EndDragDropSource();			
			}			
		}
	}
}

void TreeNode::DropCheck()
{
	if (!m_Owner->IsDrop())
		return;
	
	if (ImGui::BeginDragDropTarget())
	{
		if(m_Owner->IsEmptyDuplicateNodes())
			m_Owner->SetDroppedNode(this);
		
		ImGui::EndDragDropTarget();
	}
}

// ======
// TreeUI
// ======

TreeUI::TreeUI()
	: m_Root(nullptr)
	, m_SelectedNode(nullptr)
	, m_DuplicateNode(nullptr)
	, m_DragedNode(nullptr)
	, m_DroppedNode(nullptr)
	, m_ClickedInst(nullptr)
	, m_ClickedFunc(nullptr)
	, m_SelfDragDropInst(nullptr)
	, m_SelfDragDropFunc(nullptr)
	, m_DropInst(nullptr)
	, m_DropFunc(nullptr)
	, m_PopupInst(nullptr)
	, m_PopupFunc(nullptr)
	, m_NodeID(0)
	, m_UseDrag(false)
	, m_UseDrop(false)
	, m_ShowRoot(false)
	, m_ShowNameOnly(false)
	, m_Duplicate(false)
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

	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
	{
		if (m_DragedNode && !m_DroppedNode)
		{
			if (m_SelfDragDropInst && m_SelfDragDropFunc)
			{
				(m_SelfDragDropInst->*m_SelfDragDropFunc)((DWORD_PTR)m_DragedNode, 0);
			}
		}

		m_DragedNode = nullptr;
		m_DroppedNode = nullptr;
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

	if (!m_vecNodes.empty())
	{
		for (size_t i = 0; i < m_vecNodes.size(); ++i)
		{
			m_vecNodes[i]->m_Selected = false;
		}

		m_vecNodes.clear();
	}

	// ���ο� ��带 ���õ� ���� ����
	m_SelectedNode = _Node;
	m_DuplicateNode = nullptr;
		
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

void TreeUI::SetDragedNode(TreeNode* _Node)
{
	// Draged Node Setting
	m_DragedNode = _Node;
}
void TreeUI::SetDuplicateNode(TreeNode* _Node)
{
	if (nullptr != m_DuplicateNode)
		m_DuplicateNode->m_Selected = false;

	m_DuplicateNode = _Node;

	SetDuplicateNodes();
}
void TreeUI::SetDuplicateNodes()
{
	TreeNode* pNode = nullptr;

	for (size_t i = 0; i < m_Root->m_vecChildNode.size(); ++i)
	{
		if (m_Root->m_vecChildNode[i]->GetName() == "SPRITE" 
		 || m_Root->m_vecChildNode[i]->GetName() == "ANIMATION")
		{
			pNode = m_Root->m_vecChildNode[i];

			for (size_t i = 0; i < pNode->m_vecChildNode.size(); ++i)
			{
				if (m_SelectedNode == pNode->m_vecChildNode[i])
					m_Duplicate = true;

				if (m_Duplicate)
				{
					m_vecNodes.push_back(pNode->m_vecChildNode[i]);
					pNode->m_vecChildNode[i]->m_Selected = true;
				}

				if (m_DuplicateNode == pNode->m_vecChildNode[i])
				{
					m_Duplicate = false;
					break;
				}
			}
		}
	}
}

void TreeUI::SetDroppedNode(TreeNode* _Node)
{
	// Drag �� Node �� ���� ��� (�ܺ� �����Ͱ� Tree ������ ���� ��)
	if (nullptr == m_DragedNode)
	{
		// PayLoad �������� ����ؼ� ��� ������ �ʰ�
		const ImGuiPayload* PayLoad = ImGui::AcceptDragDropPayload(m_DropPayLoadName.c_str());
		
		if (PayLoad)
		{
			// DropNode Setting
			m_DroppedNode = _Node;
			
			// Delegate �Լ� ȣ��
			if(m_DropInst && m_DropFunc)
				(m_DropInst->*m_DropFunc)((DWORD_PTR)PayLoad->Data, (DWORD_PTR)m_DroppedNode);
		}
	}

	// Self Drag, Drop �� ��� (Outliner GameObject AddChild)
	else
	{
		// assert(Drag �� Node �� Owner(Tree)�� this�� �ƴ϶�� �翬�� assert)
		assert(m_DragedNode->m_Owner == this); 

		const ImGuiPayload* PayLoad = ImGui::AcceptDragDropPayload(m_DropPayLoadName.c_str());
		if (PayLoad)
		{
			m_DroppedNode = _Node;
			
			if(m_SelfDragDropInst && m_SelfDragDropFunc)
				(m_SelfDragDropInst->*m_SelfDragDropFunc)((DWORD_PTR)m_DragedNode, (DWORD_PTR)m_DroppedNode);
		}
	}
}

void TreeUI::PopupMenu(TreeNode* _Node)
{
	if(m_PopupInst && m_PopupFunc)
		(m_PopupInst->*m_PopupFunc)((DWORD_PTR)_Node);
}

void TreeUI::Clear()
{
	if (nullptr != m_Root)
	{
		delete m_Root;
		m_Root = nullptr;
	}
}