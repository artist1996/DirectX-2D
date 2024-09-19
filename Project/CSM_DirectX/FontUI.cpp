#include "pch.h"
#include "FontUI.h"

#include <Engine/CFont.h>

//FontUI::FontUI()
//	: ComponentUI(COMPONENT_TYPE::FONT)
//	, m_Scale(0.f)
//{
//}
//
//FontUI::~FontUI()
//{
//}
//
//void FontUI::Update()
//{
//	//Title();
//	ImGui::Text("Font");
//	ImGui::SameLine();
//
//	CFont* pFont = GetTargetObject()->Font();
//
//	static char szBuff[255] = {};
//
//	if (ImGui::InputText("##InputFont", szBuff, 255))
//	{
//		m_strFont = szBuff;
//		pFont->SetFont(wstring(m_strFont.begin(), m_strFont.end()));
//	}
//
//	ImGui::Text("Scale");
//	if (ImGui::DragFloat("##FontScale", &m_Scale))
//	{
//		pFont->SetScale(m_Scale);
//	}
//
//	if (ImGui::ColorEdit4("##FontColor", m_Color))
//	{
//		pFont->SetColor(m_Color);
//	}	
//}