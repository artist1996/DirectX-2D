#pragma once
#include <Engine/CScript.h>

class CMonsterHPBarScript :
    public CScript
{
private:
    vector<Ptr<CTexture>> m_vecTex;
    float                 m_Ratio;
    int                   m_SegmentHP;

private:
    void CalculateRatio(const INFO& _info);
    Ptr<CTexture> CalculateHPBarTex(float _TargetHP);

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CMonsterHPBarScript);
    CMonsterHPBarScript();
    virtual ~CMonsterHPBarScript();
};

