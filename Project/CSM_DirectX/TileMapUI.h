#pragma once
#include "ComponentUI.h"
class TileMapUI :
    public ComponentUI
{
private:
    UINT  m_UIHeight;
    float m_Ratio;

public:
    virtual void Update() override;

public:
    TileMapUI();
    virtual ~TileMapUI();
};