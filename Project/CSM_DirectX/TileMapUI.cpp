#include "pch.h"
#include "TileMapUI.h"

#include <Engine/CGameObject.h>
#include <Engine/CTileMap.h>

#include "TreeUI.h"

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

	string strTexKey = string(pTileMap->GetTexture()->GetKey().begin(), pTileMap->GetTexture()->GetKey().end());

	ImGui::Text("Texture");
	ImGui::SameLine();
	ImGui::InputText("##TileMapTexKey", (char*)strTexKey.c_str(), strTexKey.length(), ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;
	
			Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();
			if (ASSET_TYPE::TEXTURE == pAsset->GetAssetType())
			{
				pTileMap->SetAtlasTexture((CTexture*)pAsset.Get());
			}
		}
	
		ImGui::EndDragDropTarget();
	}

	m_UIHeight += (UINT)ImGui::GetItemRectSize().y;

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
	pTileMap->SetTileSize(TileSize);
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

	pTileMap->SetRowCol(Row, Col);

	SetChildSize(ImVec2(0.f, (float)m_UIHeight + 10.f));
}