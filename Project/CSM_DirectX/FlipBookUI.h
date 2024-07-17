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
    void Save();

public:
    FlipBookUI();
    virtual ~FlipBookUI();
};

