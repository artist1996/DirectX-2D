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
    UINT        m_ScriptType;

public:
    virtual void Tick() PURE;
    virtual void FinalTick() final override {}

    UINT GetScriptType() { return m_ScriptType; }

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}

public:
    CScript(UINT _m_ScriptType);
    virtual ~CScript();
};