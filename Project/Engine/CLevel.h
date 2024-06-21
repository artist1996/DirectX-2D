#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
private:
    CLayer*      m_Layer[MAX_LAYER];

    LEVEL_STATE  m_State;

public:
    void AddObject(int _LayerIdx, CGameObject* _Object, bool _bMoveChild = false);
    CLayer* GetLayer(int _LayderIdx) { return m_Layer[_LayderIdx]; }
    LEVEL_STATE GetState()           { return m_State; }

    CGameObject* FindObjectByName(const wstring& _strName);

    void ClearObject();
    
private:
    void ChangeLevelState(LEVEL_STATE _NextState);

public:
    void Begin();
    void Tick();
    void FinalTick();
    
public:
    virtual CLevel* Clone() { return new CLevel(*this); }
    CLevel();
    virtual ~CLevel();

    friend class CTaskMgr;
};