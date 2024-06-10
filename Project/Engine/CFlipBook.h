#pragma once
#include "CAsset.h"

class CSprite;

class CFlipBook :
    public CAsset
{
private:
    vector<CSprite*> m_vecSprite;

public:
    void FinalTick();

public:
    CFlipBook();
    virtual ~CFlipBook();
};

