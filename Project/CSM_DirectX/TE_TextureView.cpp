#include "pch.h"
#include "TE_TextureView.h"

#include <Engine/CGameObject.h>
#include <Engine/CTileMap.h>

#include "TE_Renderer.h"

TE_TextureView::TE_TextureView()
{
}

TE_TextureView::~TE_TextureView()
{
}

void TE_TextureView::Init()
{
}

void TE_TextureView::Update()
{
	if (nullptr == GetTargetObject() || !IsActive())
		return;

	CTileMap* pTileMap = GetTargetObject()->TileMap();

	ImVec2 uv_min = ImVec2(0.0f, 0.0f);
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);

	Vec2 vResolution = Vec2((float)pTileMap->GetTexture()->Width(), (float)pTileMap->GetTexture()->Height());

	
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

	ImGui::Image(pTileMap->GetTexture()->GetSRV().Get(), ImVec2(vResolution.x, vResolution.y)
		, uv_min
		, uv_max
		, tint_col, border_col);

	ClickedCheck();
}

void TE_TextureView::ClickedCheck()
{
	CTileMap* pTileMap = GetTargetObject()->TileMap();
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{		
		ImVec2 MousePos = ImGui::GetMousePos();
		m_ImageRectMin = ImGui::GetItemRectMin();
		ImVec2 TileSize = ImVec2(pTileMap->GetTileSize().x, pTileMap->GetTileSize().y);
		ImVec2 vDiff = ImVec2(MousePos.x - m_ImageRectMin.x, MousePos.y - m_ImageRectMin.y);
		int Col = pTileMap->GetTextureMaxCol();
		int Row = pTileMap->GetTextureMaxRow();

		if (vDiff.x >= 0 && vDiff.y >= 0 && vDiff.x < Col * TileSize.x && vDiff.y < Row * TileSize.y)
		{
			int ClickCol = (int)vDiff.x / (int)TileSize.x;
			int ClickRow = (int)vDiff.y / (int)TileSize.y;

			int TileIdx = Col * ClickRow + ClickCol;

			GetRenderer()->SetImgIdx(TileIdx);
		}
	}
}