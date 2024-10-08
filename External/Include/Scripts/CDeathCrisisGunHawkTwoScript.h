#pragma once
#include <Engine/CScript.h>

class CDeathCrisisGunHawkTwoScript :
    public CScript
{
private:
    Vec3         m_StartPos;
    Vec3         m_Dir;

private:
    float EaseInOut(float _x);

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CDeathCrisisGunHawkTwoScript);
    CDeathCrisisGunHawkTwoScript();
    virtual ~CDeathCrisisGunHawkTwoScript();
};

