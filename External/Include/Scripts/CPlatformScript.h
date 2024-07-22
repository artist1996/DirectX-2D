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
    CLONE(CPlatformScript);
    CPlatformScript();
    virtual ~CPlatformScript();
};

