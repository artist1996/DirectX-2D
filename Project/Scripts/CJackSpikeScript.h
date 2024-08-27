#pragma once
#include <Engine/CScript.h>

class CJackSpikeScript :
    public CScript
{
private:
    float   m_Time;
    
public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CJackSpikeScript);
    CJackSpikeScript();
    virtual ~CJackSpikeScript();
};

