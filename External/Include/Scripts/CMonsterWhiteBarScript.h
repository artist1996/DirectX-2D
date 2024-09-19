#pragma once
#include <Engine/CScript.h>

class CMonsterWhiteBarScript :
    public CScript
{
private:
    int                   m_SegmentHP;
    float                 m_HPRatio;

private:
    float Lerp(float _start, float _end, float _t);
    float CalculateRatio(float _TargetHP);

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CMonsterWhiteBarScript);
    CMonsterWhiteBarScript();
    virtual ~CMonsterWhiteBarScript();
};