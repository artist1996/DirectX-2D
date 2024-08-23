#pragma once
#include <Engine/CScript.h>

class CPlayerJumpScript :
    public CScript
{
private:
    bool m_NormalJump;

private:
    void Jump();
    void AxisCheck();

public:
    bool IsNormalJump() { return m_NormalJump; }

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CPlayerJumpScript);
    CPlayerJumpScript();
    virtual ~CPlayerJumpScript();
};

