#pragma once
#include <Engine/CScript.h>

class CDiagonalHeadShotScript :
    public CScript
{
private:
    Ptr<CPrefab> m_HitEffectPref;
    float        m_DestroyPos;
    float        m_Speed;

private:

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;

public:
    CLONE(CDiagonalHeadShotScript);
    CDiagonalHeadShotScript();
    virtual ~CDiagonalHeadShotScript();
};

