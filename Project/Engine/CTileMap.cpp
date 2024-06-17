#include "pch.h"
#include "CTileMap.h"

#include "CAssetMgr.h"
#include "CTransform.h"

#include "CStructuredBuffer.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_TileAtlas(nullptr)
	, m_Buffer(nullptr)
	, m_Row(1)
	, m_Col(1)
	, m_AtlasMaxRow(0)
	, m_AtlasMaxCol(0)
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"TileMapMtrl"));

	m_Buffer = new CStructuredBuffer;
}

CTileMap::~CTileMap()
{
	delete m_Buffer;
}

void CTileMap::FinalTick()
{
}

void CTileMap::Render()
{
	m_Buffer->SetData(m_vecTileInfo.data(), sizeof(tTileInfo) * m_Row * m_Col);
	m_Buffer->Binding(15);

	GetMaterial()->SetTexParam(TEX_0, m_TileAtlas);
	GetMaterial()->SetScalarParam(INT_1, m_AtlasMaxRow);
	GetMaterial()->SetScalarParam(INT_2, m_AtlasMaxCol);
	GetMaterial()->SetScalarParam(VEC2_0, m_AtlasSliceUV);
	GetMaterial()->SetScalarParam(VEC2_1, Vec2((float)m_Col, (float)m_Row));

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
	
	// 타일 개수
	UINT TileCount = m_Row * m_Col;

	// 타일 정보를 저장하는 벡터 사이즈가 타일 카운트보다 사이즈가 작다면 resize 해준다.
	if (m_vecTileInfo.size() < TileCount)
	{
		m_vecTileInfo.resize(TileCount);

		for (size_t i = 0; i < m_vecTileInfo.size(); ++i)
		{
			m_vecTileInfo[i].ImgIdx = 0;
		}
	}

	// 타일 정보를 전달받아서 t 레지스터에 전달시킬 구조화 버퍼가 타일 전체 데이터 사이즈 보다 작으면 리사이즈
	if (m_Buffer->GetElementSize() < sizeof(tTileInfo) * TileCount)
	{
		m_Buffer->Create(sizeof(tTileInfo), TileCount);
	}
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