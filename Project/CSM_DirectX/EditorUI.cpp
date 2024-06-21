#include "pch.h"
#include "EditorUI.h"

UINT EditorUI::m_GlobalID = 0;

EditorUI::EditorUI()
	: m_ID(m_GlobalID++)
	, m_Parent(nullptr)
	, m_Active(true)
	, m_ChildBorder(false)
{
}

EditorUI::~EditorUI()
{
	Delete_Vec(m_vecChildren);
}

void EditorUI::Tick()
{
	if (!m_Active)
		return;
		
	if (nullptr == m_Parent)
	{
		ImGui::Begin(m_Name.c_str(), &m_Active);

		Update();

		for (size_t i = 0; i < m_vecChildren.size(); ++i)
		{
			if (m_vecChildren[i]->m_ChildBorder)
				ImGui::Separator();

			m_vecChildren[i]->Tick();
			
			if (m_vecChildren[i]->m_ChildBorder && i == m_vecChildren.size() - 1)
				ImGui::Separator();
		}

		ImGui::End();
	}
	else
	{
		ImGui::BeginChild(m_Name.c_str(), m_ChildSize);

		Update();

		for (size_t i = 0; i < m_vecChildren.size(); ++i)
		{
			if (m_vecChildren[i]->m_ChildBorder)
				ImGui::Separator();

			m_vecChildren[i]->Tick();

			if (m_vecChildren[i]->m_ChildBorder && i == m_vecChildren.size() - 1)
				ImGui::Separator();
		}

		ImGui::EndChild();
	}
}

void EditorUI::AddChild(EditorUI* _UI)
{
	_UI->m_Parent = this;
	m_vecChildren.push_back(_UI);
}

void EditorUI::SetName(const string& _strName)
{
	m_Name = _strName;

	m_FullName = m_Name;
	
	char szBuff[50] = {};
	_itoa_s(m_ID, szBuff, 10);
	m_FullName = m_FullName + "##" + szBuff;
}
