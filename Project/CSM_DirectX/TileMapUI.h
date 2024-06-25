#pragma once
#include "ComponentUI.h"
class TileMapUI :
    public ComponentUI
{
private:

public:
    virtual void Update() override;

public:
    TileMapUI();
    virtual ~TileMapUI();
};

