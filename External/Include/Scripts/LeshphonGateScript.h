#pragma once
#include <Engine/CScript.h>

enum class GATE_TYPE
{
    LESHPHON1,
    LESHPHON2,
    LESHPHON3,

    END,
};

class LeshphonGateScript :
    public CScript
{
private:
    GATE_TYPE m_Type;

private:

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;

public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(LeshphonGateScript);
    LeshphonGateScript();
    virtual ~LeshphonGateScript();

};

