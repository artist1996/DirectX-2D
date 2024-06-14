#pragma once
#include "CRenderComponent.h"

class CTileMap :
    public CRenderComponent
{
private:
    Ptr<CTexture> m_TileAtlas;       // Tile ���� �̹������� ���� �ϰ� �ִ� ��Ʋ�� �ؽ���

    UINT          m_Row;             // TileMap�� �� ����
    UINT          m_Col;             // TileMap�� �� ����
    Vec2          m_TileSize;        // Tile 1���� ũ��
                  
    Vec2          m_AtlasResolution; // Atlas Texture �ػ�       
    Vec2          m_AtlasTileSize;   // Atlas �ؽ��� ������ Ÿ�� 1���� ũ��
    Vec2          m_AtlasSliceUV;    // Atlas �ؽ��� ������ Ÿ�� 1���� ũ�⸦ UV �� ��ȯ�� ũ��(SliceUV)

    int           m_AtlasMaxRow;     // Atlas �ؽ��İ� �����ϰ� �ִ� Ÿ���� �ִ� �� ����   
    int           m_AtlasMaxCol;     // Atlas �ؽ��İ� �����ϰ� �ִ� Ÿ���� �ִ� �� ����

    int           m_ImgIdx;          // 0�� ���� (m_AtlasMaxRow * m_AtlasMaxCol - 1) ���� ��� ����

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

