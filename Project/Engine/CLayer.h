#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*> m_Parents;

public:
    void Init();

    void Tick();
    void FinalTick();
    void Render();

public:
    virtual CLayer* Clone() { return new CLayer(*this); }
    CLayer();
    virtual ~CLayer();
};

