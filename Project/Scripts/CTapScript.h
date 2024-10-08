#pragma once
#include <Engine/CScript.h>

class CTapScript :
    public CScript
{
private:
    Ptr<CTexture> m_Tex;
    wstring       m_strFont;
    TAP_TYPE      m_Type;

private:
    void SetFont();

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CTapScript);
    CTapScript();
    virtual ~CTapScript();
};

