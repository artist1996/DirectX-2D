#pragma once
#include "AssetUI.h"
class AnimationUI :
    public AssetUI
{
private:

public:
    virtual void Update() override;

private:
    void AddFrame();
    void Save();

public:
    AnimationUI();
    virtual ~AnimationUI();
};

