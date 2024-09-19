#pragma once
#include <Engine/CScript.h>

class CPlayerMPHUDScript :
    public CScript
{
private:
    CGameObject* m_pTarget;
    float        m_Ratio;

private:
    void CalculateByRatio(INFO& _info);

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   {}
    virtual void LoadFromFile(FILE* _pFile) {}

public:
    CLONE(CPlayerMPHUDScript);
    CPlayerMPHUDScript();
    virtual ~CPlayerMPHUDScript();
};

