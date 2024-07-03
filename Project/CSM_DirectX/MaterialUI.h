#pragma once
#include "AssetUI.h"
class MaterialUI :
    public AssetUI
{
private:

public:
    virtual void Update() override;

public:
    MaterialUI();
    virtual ~MaterialUI();
};

