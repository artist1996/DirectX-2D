#pragma once
#include "CScript.h"
class CPlayerScript :
    public CScript
{
private:
    float m_Speed;

public:
    virtual void Tick() override;

public:
    CLONE(CPlayerScript);
    CPlayerScript();
    virtual ~CPlayerScript();
};

