#pragma once
#include <Engine/CScript.h>

class CStorePriceScript :
    public CScript
{
private:
    wstring      m_strFont;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CStorePriceScript);
    CStorePriceScript();
    virtual ~CStorePriceScript();
};

