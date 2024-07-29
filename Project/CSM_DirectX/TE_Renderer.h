#pragma once
#include "TE_Sub.h"
class TE_Renderer :
    public TE_Sub
{
private:
    vector<class CGameObject*> m_vecTiles;

    ImVec2                     m_TileSize;
   
    int                        m_TileIdx;

    bool                       m_UseGrid;
    
private:
    void Render();

public:
    void UseGrid(bool _Use) { m_UseGrid = _Use; }

public:
    virtual void Init() override;
    virtual void Update() override;

public:
    TE_Renderer();
    virtual ~TE_Renderer();
};