#pragma once
#include "CRenderComponent.h"

class CTileMap :
    public CRenderComponent
{
private:
    Ptr<CTexture> m_TileAtlas;       // Tile 개별 이미지들을 보유 하고 있는 아틀라스 텍스쳐

    UINT          m_Row;             // TileMap의 행 숫자
    UINT          m_Col;             // TileMap의 열 숫자
    Vec2          m_TileSize;        // Tile 1개의 크기
                  
    Vec2          m_AtlasResolution; // Atlas Texture 해상도       
    Vec2          m_AtlasTileSize;   // Atlas 텍스쳐 내에서 타일 1개의 크기
    Vec2          m_AtlasSliceUV;    // Atlas 텍스쳐 내에서 타일 1개의 크기를 UV 로 변환한 크기(SliceUV)

    int           m_AtlasMaxRow;     // Atlas 텍스쳐가 보유하고 있는 타일의 최대 행 숫자   
    int           m_AtlasMaxCol;     // Atlas 텍스쳐가 보유하고 있는 타일의 최대 열 숫자

    int           m_ImgIdx;          // 0번 부터 (m_AtlasMaxRow * m_AtlasMaxCol - 1) 까지 사용 가능

public:
    void SetRowCol(UINT _Row, UINT _Col);
    void SetTileSize(Vec2 _Size);
    void SetAtlasTexture(Ptr<CTexture> _Atlas);
    void SetAtlasTileSize(Vec2 _TileSize);

private:
    void ChangeTileMapSize();

public:
    virtual void FinalTick() override;
    virtual void Render() override;

public:
    CLONE(CTileMap);
    CTileMap();
    virtual ~CTileMap();
};

