#pragma once
#include "TE_Sub.h"
class TE_Renderer :
    public TE_Sub
{
private:
    int                        m_TileIdx;
    bool                       m_UseGrid;
    int                        m_TileImgIdx;
    
    ImVec2                     TilePos;

private:
    void RenderGrid();
    void RenderTileMap();

public:
    void UseGrid(bool _Use)  { m_UseGrid = _Use; }
    void SetImgIdx(int _Idx) { m_TileImgIdx = _Idx; }

public:
    virtual void Init() override;
    virtual void Update() override;

public:
    TE_Renderer();
    virtual ~TE_Renderer();
};