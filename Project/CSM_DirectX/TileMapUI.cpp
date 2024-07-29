#include "pch.h"
#include "TileMapUI.h"

#include <Engine/CGameObject.h>
#include <Engine/CTileMap.h>

TileMapUI::TileMapUI()
	: ComponentUI(COMPONENT_TYPE::TILEMAP)
	, m_UIHeight(0)
{
}

TileMapUI::~TileMapUI()
{
}


void TileMapUI::Update()
{
	m_UIHeight = 0;
	Title();
	m_UIHeight += (UINT)ImGui::GetItemRectSize().y;

	CTileMap* pTileMap = GetTargetObject()->TileMap();

	ImGui::Text("Texture");

	m_UIHeight += (UINT)ImGui::GetItemRectSize().y;

	ImTextureID TexID = nullptr;

	if (nullptr != pTileMap->GetTexture())
		TexID = pTileMap->GetTexture()->GetSRV().Get();


	ImVec2 ImageSize = ImVec2((float)pTileMap->GetTexture()->Width(), (float)pTileMap->GetTexture()->Height());

	ImGui::Image(TexID, ImageSize, ImVec2(0.f, 0.f), ImVec2(1.f, 1.f));

	m_UIHeight += (UINT)ImGui::GetItemRectSize().y + 20.f;
	
	int MaxIdx = pTileMap->GetTileMaxIdx();

	ImGui::Text("Index");
	ImGui::SameLine(64.f);
	ImGui::InputInt("##TileMaxIndex", &MaxIdx, 0, ImGuiInputTextFlags_ReadOnly);
	m_UIHeight += (UINT)ImGui::GetItemRectSize().y;

	Vec2 TileSize = pTileMap->GetTileSize();
	ImGui::Text("TileSize");
	ImGui::SameLine();
	ImGui::InputFloat2("##TileSize", (float*)&TileSize);
	m_UIHeight += (UINT)ImGui::GetItemRectSize().y;

	int Row = pTileMap->GetRow();
	int Col = pTileMap->GetCol();

	ImGui::Text("Tile Row");
	ImGui::SameLine();
	ImGui::InputInt("##TileMapRow", &Row);
	m_UIHeight += (UINT)ImGui::GetItemRectSize().y;

	ImGui::Text("Tile Col");
	ImGui::SameLine();
	ImGui::InputInt("##TileMapRow", &Col);
	m_UIHeight += (UINT)ImGui::GetItemRectSize().y;

	SetChildSize(ImVec2(0.f, (float)m_UIHeight + 10.f));
}