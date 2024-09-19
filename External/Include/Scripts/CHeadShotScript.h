#pragma once
#include <Engine/CScript.h>
class CHeadShotScript :
    public CScript
{
private:
    Ptr<CPrefab> m_HitEffectPref;
    bool         m_Hit;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    
public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;

public:
    CLONE(CHeadShotScript);
    CHeadShotScript();
    virtual ~CHeadShotScript();
};

