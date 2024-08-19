#pragma once
#include <Engine/CScript.h>

class CPlatformScript :
    public CScript
{
private:
    PLATFORM_TYPE m_Type;
    
public:
    void SetType(PLATFORM_TYPE _Type) { m_Type = _Type; }

public:
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)   override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CPlatformScript);
    CPlatformScript();
    virtual ~CPlatformScript();
};

