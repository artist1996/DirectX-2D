#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
private:
    CLayer* m_Layer[MAX_LAYER];

public:
    void AddObject(int _LayerIdx, CGameObject* _Object);
    CLayer* GetLayer(int _LayderIdx) { return m_Layer[_LayderIdx]; }

public:
    void Begin();
    void Tick();
    void FinalTick();
    
public:
    virtual CLevel* Clone() { return new CLevel(*this); }
    CLevel();
    virtual ~CLevel();
};