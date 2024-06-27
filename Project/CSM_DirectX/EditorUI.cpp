#include "pch.h"
#include "EditorUI.h"

UINT EditorUI::m_GlobalID = 0;

EditorUI::EditorUI()
	: m_ID(m_GlobalID++)
	, m_Parent(nullptr)
	, m_Active(true)
	, m_ChildBorder(false)
	, m_Modal(false)
{
}

EditorUI::~EditorUI()
{
	Delete_Vec(m_vecChildUI);
}

void EditorUI::Tick()
{
	if (!m_Active)
		return;

	bool bActive = m_Active;
		

	if (nullptr == m_Parent)
	{
		// Modaless
		if (false == m_Modal)
		{
			ImGui::Begin(m_FullName.c_str(), &bActive);

			if (m_Active != bActive)
			{
				SetActive(bActive);
			}

			Update();

			for (size_t i = 0; i < m_vecChildUI.size(); ++i)
			{
				m_vecChildUI[i]->Tick();

				if (m_vecChildUI[i]->m_ChildBorder && i == m_vecChildUI.size() - 1)
					ImGui::Separator();
			}

			ImGui::End();
		}
		
		// Modal
		else
		{
			ImGui::OpenPopup(m_FullName.c_str());

			if (ImGui::BeginPopupModal(m_FullName.c_str(), &bActive))
			{
				if (m_Active != bActive)
				{
					SetActive(bActive);
				}

				Update();

				for (size_t i = 0; i < m_vecChildUI.size(); ++i)
				{
					m_vecChildUI[i]->Tick();

					if (m_vecChildUI[i]->m_ChildBorder && i == m_vecChildUI.size() - 1)
						ImGui::Separator();
				}

				ImGui::EndPopup();
			}
		}
	}

	// 자식 타입의 UI인 경우
	else
	{
		if (m_ChildBorder)
		{
			ImGui::Separator();
		}

		ImGui::BeginChild(m_FullName.c_str(), m_ChildSize);

		Update();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			if (m_vecChildUI[i]->m_ChildBorder)
				ImGui::Separator();

			m_vecChildUI[i]->Tick();

			if (m_vecChildUI[i]->m_ChildBorder && i == m_vecChildUI.size() - 1)
				ImGui::Separator();
		}

		ImGui::EndChild();
	}
}

void EditorUI::AddChild(EditorUI* _UI)
{
	_UI->m_Parent = this;
	m_vecChildUI.push_back(_UI);
}

void EditorUI::SetName(const string& _strName)
{
	m_Name = _strName;

	m_FullName = m_Name;
	
	char szBuff[50] = {};
	_itoa_s(m_ID, szBuff, 10);
	m_FullName = m_FullName + "##" + szBuff;
}

void EditorUI::SetActive(bool _Active)
{
	if (m_Active == _Active)
		return;

	m_Active = _Active;

	if (m_Active)
		Activate();
	else
		Deactivate();
}