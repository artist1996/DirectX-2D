#pragma once
#include <Engine/CScript.h>

class CBossMaxHPBarScript :
    public CScript
{
private:
    CGameObject* m_pTarget;
    float        m_Ratio;

private:
    void CalculateRatio(INFO& _info);

public:
    virtual void Begin() override;
    virtual void Tick()  override;

public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CBossMaxHPBarScript);
    CBossMaxHPBarScript();
    virtual ~CBossMaxHPBarScript();
};

