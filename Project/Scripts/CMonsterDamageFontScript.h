#pragma once
#include <Engine/CScript.h>

enum class FONT_TYPE
{
    NORMAL,
    CRITICAL,
    END,
};

class CMonsterDamageFontScript :
    public CScript
{
private:
    wstring   m_strFont;
    float     m_Time;
    int       m_Damage;
    
    FONT_TYPE m_Type;

public:
    void SetType(FONT_TYPE _Type) { m_Type = _Type; }
    void SetDamge(int _Damage)    { m_Damage = _Damage; }

public:
    virtual void Begin() override;
    virtual void Tick()  override;

public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CMonsterDamageFontScript);
    CMonsterDamageFontScript();
    virtual ~CMonsterDamageFontScript();
};

