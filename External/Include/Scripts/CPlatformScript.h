#pragma once
#include <Engine/CScript.h>

class CPlatformScript :
    public CScript
{
private:

public:
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CPlatformScript);
    CPlatformScript();
    virtual ~CPlatformScript();
};

