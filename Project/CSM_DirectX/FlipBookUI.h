#pragma once
#include "AssetUI.h"
class FlipBookUI :
    public AssetUI
{
private:

public:
    virtual void Update() override;

private:
    void AddFrame();

public:
    FlipBookUI();
    virtual ~FlipBookUI();
};

