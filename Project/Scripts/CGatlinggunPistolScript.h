#pragma once
#include <Engine/CScript.h>

class CGatlinggunPistolScript :
    public CScript
{
private:
    float   m_Speed;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CGatlinggunPistolScript);
    CGatlinggunPistolScript();
    virtual ~CGatlinggunPistolScript();
};

