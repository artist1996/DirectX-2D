#pragma once
#include "CEntity.h"

class CMesh;
class CGraphicShader;

class CGameObject :
    public CEntity
{
private:
    
public:
    void Tick();
    void FinalTick();
    void Render();

public:
    virtual CGameObject* Clone() { return new CGameObject(*this); }
    CGameObject();
    virtual ~CGameObject();
};

