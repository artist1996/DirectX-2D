#include "pch.h"
#include "TE_Renderer.h"

#include <Engine/CKeyMgr.h>
#include <Engine/CGameObject.h>
#include <Engine/CTileMap.h>

TE_Renderer::TE_Renderer()
	: m_TileIdx(0)
	, m_TileImgIdx(0)
	, m_UseGrid(false)

{
}

TE_Renderer::~TE_Renderer()
{
}

void TE_Renderer::Init()
{
}

void TE_Renderer::Update()
{
	if (!IsActive() || !GetTargetObject())
		return;

	//CTileMap* pTileMap = GetTargetObject()->TileMap();
	
	RenderTileMap();
}

void TE_Renderer::RenderGrid()
{
	CTileMap* pTileMap = GetTargetObject()->TileMap();
}

void TE_Renderer::RenderTileMap()
{
	CTileMap* pTileMap = GetTargetObject()->TileMap();
	

	int Row = pTileMap->GetRow();
	int Col = pTileMap->GetCol();
	int TexMaxRow = pTileMap->GetTextureMaxRow();
	int TexMaxCol = pTileMap->GetTextureMaxCol();
	Ptr<CTexture> pTexture = pTileMap->GetTexture();
	Vec2 TileSize = pTileMap->GetTileSize();
	Vec2 TexTileSize = pTileMap->GetTextureTileSize();
	Vec2 SliceUV = pTileMap->GetSliceUV();

	UINT Width = pTexture->Width();
	UINT Height = pTexture->Height();
	Vec2 TileMapSize = Vec2(Row, Col) * TileSize;

	ImVec2 canvasPos = ImGui::GetCursorScreenPos();

	ImDrawList* drawList = ImGui::GetWindowDrawList();

	for (int i = 0; i < Row; ++i)
	{	
		for (int j = 0; j < Col; ++j)
		{
			m_TileIdx = Col * i + j;
			
			int ImgIdx = pTileMap->GetTileInfoIdx(m_TileIdx);

			if (-1 != ImgIdx)
			{
				TilePos = ImVec2(canvasPos.x + j * TileSize.x, canvasPos.y + i * TileSize.y);

				UINT TileImgRow = ImgIdx / TexMaxCol;
				UINT TileImgCol = ImgIdx % TexMaxCol;

				Vec2 vCurColRow = Vec2(TileImgCol, TileImgRow);

				// 타일의 UV 좌표 계산
				ImVec2 uv0 = ImVec2(vCurColRow.x * SliceUV.x, vCurColRow.y * SliceUV.y);
				ImVec2 uv1 = ImVec2(uv0.x + TileSize.x / pTexture->Width(), uv0.y + TileSize.y / pTexture->Height());

				//ImGui::Image(pTexture->GetSRV().Get(), ImVec2(pTexture->Width(), pTexture->Height()), uv0, uv1);
				drawList->AddImage(pTexture->GetSRV().Get(), TilePos, ImVec2(TilePos.x + TileSize.x, TilePos.y + TileSize.y), uv0, uv1);
			}
		}
	}

	if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		ImVec2 MousePos = ImGui::GetMousePos();
		ImVec2 vDiff = ImVec2(MousePos.x - canvasPos.x, MousePos.y - canvasPos.y);
		if (vDiff.x >= 0 && vDiff.y >= 0 && vDiff.x < Col * TileSize.x && vDiff.y < Row * TileSize.y)
		{
			int ClickCol = static_cast<int>(vDiff.x / TileSize.x);
			int ClickRow = static_cast<int>(vDiff.y / TileSize.y);

			m_TileIdx = Col * ClickRow + ClickCol;

			pTileMap->SetTileIdx(m_TileIdx, m_TileImgIdx);
		}
	}
}
