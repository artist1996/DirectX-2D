#pragma once
#include <Engine/CScript.h>

class CDirezieWindScript :
    public CScript
{
private:
    float m_Time;
    float m_HitTime;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)      override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)   override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CDirezieWindScript);
    CDirezieWindScript();
    virtual ~CDirezieWindScript();
};

