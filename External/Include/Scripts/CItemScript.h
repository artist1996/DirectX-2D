#pragma once
#include <Engine/CScript.h>

class CItemScript :
    public CScript
{
private:
    ITEM_TYPE m_Type;
    bool      m_Equip;

private:
    void MouseCheck();
    void Equipment();
    void UnEquipment();

    void Sound();

public:
    void SetEquip(bool _Equip) { m_Equip = _Equip; }

public:
    virtual void Begin() override;
    virtual void Tick()  override;

public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CItemScript);
    CItemScript();
    virtual ~CItemScript();
};

