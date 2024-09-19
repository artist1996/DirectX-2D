#pragma once
#include <Engine/CScript.h>

class CMonsterNextHPBarScript :
    public CScript
{
private:
    vector<Ptr<CTexture>> m_vecTex;
    int                   m_SegmentHP;

private:
    float CalculateRatio(float _TargetHP);
    Ptr<CTexture> CalculateHPBarTex(float _TargetHP);

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CMonsterNextHPBarScript);
    CMonsterNextHPBarScript();
    virtual ~CMonsterNextHPBarScript();
};

