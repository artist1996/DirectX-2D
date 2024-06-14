#include "pch.h"
#include "CTileMap.h"

#include "CAssetMgr.h"
#include "CTransform.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_TileAtlas(nullptr)
	, m_Row(1)
	, m_Col(1)
	, m_AtlasMaxRow(0)
	, m_AtlasMaxCol(0)
	, m_ImgIdx(0)
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"TileMapMtrl"));
}

CTileMap::~CTileMap()
{
}

void CTileMap::FinalTick()
{
}

void CTileMap::Render()
{
	GetMaterial()->SetTexParam(TEX_0, m_TileAtlas);
	GetMaterial()->SetScalarParam(INT_0, m_ImgIdx);
	GetMaterial()->SetScalarParam(INT_1, m_AtlasMaxRow);
	GetMaterial()->SetScalarParam(INT_2, m_AtlasMaxCol);
	GetMaterial()->SetScalarParam(VEC2_0, m_AtlasSliceUV);

	GetMaterial()->Binding();
	Transform()->Binding();
	GetMesh()->Render();
}

void CTileMap::SetRowCol(UINT _Row, UINT _Col)
{
	// Row 와 Col 이 바뀌면 TileMap 크기도 변해야한다.
	m_Row = _Row;
	m_Col = _Col;;

	ChangeTileMapSize();
}

void CTileMap::SetTileSize(Vec2 _Size)
{
	// TileSize 가 변경되면 TileMap 크기도 변해야한다.
	m_TileSize = _Size;

	ChangeTileMapSize();
}

void CTileMap::ChangeTileMapSize()
{
	Vec2 vSize = m_TileSize * Vec2((float)m_Col, (float)m_Row);	
	Transform()->SetRelativeScale(Vec3(vSize.x, vSize.y, 1.f));
}

void CTileMap::SetAtlasTexture(Ptr<CTexture> _Atlas)
{
	m_TileAtlas = _Atlas;
	m_AtlasResolution = Vec2((float)m_TileAtlas->Width(), (float)m_TileAtlas->Height());

	SetAtlasTileSize(m_AtlasTileSize);
}

void CTileMap::SetAtlasTileSize(Vec2 _TileSize)
{
	m_AtlasTileSize = _TileSize;

	if (nullptr != m_TileAtlas)
	{
		m_AtlasSliceUV = m_AtlasTileSize / m_AtlasResolution;

		m_AtlasMaxCol = m_AtlasResolution.x / m_AtlasTileSize.x;
		m_AtlasMaxRow = m_AtlasResolution.y / m_AtlasTileSize.y;
	}
}