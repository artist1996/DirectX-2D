#pragma once
#include <Engine/CScript.h>

class CDeathCrisisGunHawkScript :
    public CScript
{
private:
    Vec3         m_StartPos;
    Vec3         m_Dir;
    
    
public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;

public:
    CLONE(CDeathCrisisGunHawkScript);
    CDeathCrisisGunHawkScript();
    virtual ~CDeathCrisisGunHawkScript();
};

