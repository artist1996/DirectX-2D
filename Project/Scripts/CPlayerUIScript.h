#pragma once
#include <Engine/CScript.h>

class CPlayerUIScript :
    public CScript
{
private:
    CGameObject* m_pTarget;
    Vec2         m_Offset;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CPlayerUIScript);
    CPlayerUIScript();
    virtual ~CPlayerUIScript();
};

