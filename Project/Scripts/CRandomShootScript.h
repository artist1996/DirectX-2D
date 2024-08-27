#pragma once
#include <Engine/CScript.h>

class CRandomShootScript :
    public CScript
{
private:
    int m_Count;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CRandomShootScript);
    CRandomShootScript();
    virtual ~CRandomShootScript();
};

