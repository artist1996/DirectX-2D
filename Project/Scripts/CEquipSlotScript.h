#pragma once
#include <Engine/CScript.h>

class CEquipSlotScript :
    public CScript
{
private:
    SLOT_TYPE   m_SlotType;
    ITEM_TYPE   m_ItemType;

private:
    void MouseCheck();

private:
    void Click();

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;


public:
    CLONE(CEquipSlotScript);
    CEquipSlotScript();
    virtual ~CEquipSlotScript();
};

