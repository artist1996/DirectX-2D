#pragma once
#include <Engine/CScript.h>

class CBossCurHPFontScript :
    public CScript
{
private:
    CGameObject* m_pTarget;
    wstring      m_strPath;

    int          m_Ratio;

private:
    void CalculateRatio(INFO& _info);
    void SetTexture();

public:
    virtual void Begin() override;
    virtual void Tick()  override;
    
public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CBossCurHPFontScript);
    CBossCurHPFontScript();
    virtual ~CBossCurHPFontScript();
};

