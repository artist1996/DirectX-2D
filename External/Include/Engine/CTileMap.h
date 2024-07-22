#pragma once
#include "CRenderComponent.h"

class CStructuredBuffer;

struct tTileInfo
{
    int ImgIdx;
    int Padding[3];
};

class CTileMap :
    public CRenderComponent
{
private:
    Ptr<CTexture>      m_TileAtlas;       // Tile ���� �̹������� ���� �ϰ� �ִ� ��Ʋ�� �ؽ���

    int                m_Row;             // TileMap�� �� ����
    int                m_Col;             // TileMap�� �� ����
    Vec2               m_TileSize;        // Tile 1���� ũ��
                       
    Vec2               m_AtlasResolution; // Atlas Texture �ػ�       
    Vec2               m_AtlasTileSize;   // Atlas �ؽ��� ������ Ÿ�� 1���� ũ��
    Vec2               m_AtlasSliceUV;    // Atlas �ؽ��� ������ Ÿ�� 1���� ũ�⸦ UV �� ��ȯ�� ũ��(SliceUV)

    int                m_AtlasMaxRow;     // Atlas �ؽ��İ� �����ϰ� �ִ� Ÿ���� �ִ� �� ����   
    int                m_AtlasMaxCol;     // Atlas �ؽ��İ� �����ϰ� �ִ� Ÿ���� �ִ� �� ����

    vector<tTileInfo>  m_vecTileInfo;     // ������ Ÿ�� ����
    CStructuredBuffer* m_Buffer;          // ����ȭ ����


public:
    virtual void Init() override;

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
    CTileMap(const CTileMap& _Origin);
    virtual ~CTileMap();
};

