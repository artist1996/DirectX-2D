#pragma once
#include "AssetUI.h"
class PrefabUI :
    public AssetUI
{
private:

public:
    virtual void Update() override;

public:
    PrefabUI();
    virtual ~PrefabUI();
};

