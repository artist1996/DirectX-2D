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

	string strName = m_strName;

	// NameOnly
	if (m_Owner->IsShowNameOnly())
	{
		path Path = strName;
		strName = Path.stem().string();
	}

	if (ImGui::TreeNodeEx(strName.c_str(), Flags))
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
			m_Owner->SetSelectedNode(this);

		DragCheck();
		DropCheck();

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
			TreeNode* pDragNode = this;
			ImGui::SetDragDropPayload(m_Owner->GetName().c_str(), &pDragNode, sizeof(TreeNode*));
			ImGui::Text(m_strName.c_str());
			ImGui::EndDragDropSource();

			m_Owner->SetDragedNode(this);
		}
	}
}

void TreeNode::DropCheck()
{
	if (!m_Owner->IsDrop())
		return;
	
	if (ImGui::BeginDragDropTarget())
	{
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
	, m_DragedNode(nullptr)
	, m_DroppedNode(nullptr)
	, m_ClickedInst(nullptr)
	, m_ClickedFunc(nullptr)
	, m_SelfDragDropInst(nullptr)
	, m_SelfDragDropFunc(nullptr)
	, m_DropInst(nullptr)
	, m_DropFunc(nullptr)
	, m_NodeID(0)
	, m_UseDrag(false)
	, m_UseDrop(false)
	, m_ShowRoot(false)
	, m_ShowNameOnly(false)
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
	// Node 생성 및 ID, Data 세팅
	TreeNode* pNode = new TreeNode(m_NodeID++);
	pNode->m_Owner = this;
	pNode->SetName(_strName);
	pNode->m_Data = _Data;
	
	// 부모가 지정되지 않으면 Root Node 로 지정
	if (nullptr == _Parent)
	{
		assert(!m_Root);

		m_Root = pNode;
	}	
	// 그게 아니라면 해당 부모의 자식으로 연결
	else
	{
		_Parent->AddChildNode(pNode);
	}

	return pNode;
}

void TreeUI::SetSelectedNode(TreeNode* _Node)
{
	// 기존에 선택 상태였던 Node를 해제
	if (nullptr != m_SelectedNode)
		m_SelectedNode->m_Selected = false;

	// 새로운 노드를 선택된 노드로 갱신
	m_SelectedNode = _Node;

	// 새로운 노드를 선택된 상태로 변경 후 함수포인터 호출
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
void TreeUI::SetDroppedNode(TreeNode* _Node)
{
	// Drag 된 Node 가 없는 경우 (외부 데이터가 Tree 안으로 들어올 때)
	if (nullptr == m_DragedNode)
	{
		// PayLoad 조건으로 사용해서 계속 들어오지 않게
		const ImGuiPayload* PayLoad = ImGui::AcceptDragDropPayload(m_DropPayLoadName.c_str());
		
		if (PayLoad)
		{
			// DropNode Setting
			m_DroppedNode = _Node;
			
			// Delegate 함수 호출
			if(m_DropInst && m_DropFunc)
				(m_DropInst->*m_DropFunc)((DWORD_PTR)PayLoad->Data, (DWORD_PTR)m_DroppedNode);
		}
	}

	// Self Drag, Drop 인 경우 (Outliner GameObject AddChild)
	else
	{
		// assert(Drag 된 Node 의 Owner(Tree)가 this가 아니라면 당연히 assert)
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



void TreeUI::Clear()
{
	if (nullptr != m_Root)
	{
		delete m_Root;
		m_Root = nullptr;
	}
}