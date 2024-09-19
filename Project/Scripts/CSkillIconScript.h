#pragma once
#include <Engine/CScript.h>

class CSkillIconScript :
    public CScript
{
private:
    CGameObject*          m_pTarget;
    PLAYER_SKILLTYPE      m_Type;
    float                 m_Ratio;


private:
    void CalculateRatio();

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile);
    virtual void LoadFromFile(FILE* _pFile);

public:
    CLONE(CSkillIconScript);
    CSkillIconScript();
    virtual ~CSkillIconScript();
};