#pragma once
#include <Engine/CScript.h>

class CBossCurHPBarScript :
    public CScript
{
private:
    vector<Ptr<CTexture>> m_vecHPBarTex;
    CGameObject*          m_Target;
    int                   m_SegmentHP;
    float                 m_HPRatio;

private:
    float Lerp(float _start, float _end, float _t);
    float CalculateRatio(float _TargetHP);
    Ptr<CTexture> CalculateHPBarTex(float _TargetHP);

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CBossCurHPBarScript);
    CBossCurHPBarScript();
    virtual ~CBossCurHPBarScript();
};

