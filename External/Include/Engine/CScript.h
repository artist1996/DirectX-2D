#pragma once
#include "CComponent.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"
#include "components.h"

class CScript :
    public CComponent
{
private:

public:
    virtual void Tick() PURE;
    virtual void FinalTick() final override {}

public:
    CScript();
    virtual ~CScript();
};