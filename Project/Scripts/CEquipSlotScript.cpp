#include "pch.h"
#include "CEquipSlotScript.h"

CEquipSlotScript::CEquipSlotScript()
	: CScript(SCRIPT_TYPE::EQUIPSLOTSCRIPT)
	, m_SlotType(SLOT_TYPE::EQUIP)
	, m_ItemType(ITEM_TYPE::END)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_ItemType);
}

CEquipSlotScript::~CEquipSlotScript()
{
}

void CEquipSlotScript::MouseCheck()
{
}

void CEquipSlotScript::Click()
{
}

void CEquipSlotScript::Begin()
{

}

void CEquipSlotScript::Tick()
{
}

void CEquipSlotScript::SaveToFile(FILE* _pFile)
{
	//fwrite(&m_ItemType, sizeof(ITEM_TYPE), 1, _pFile);
}

void CEquipSlotScript::LoadFromFile(FILE* _pFile)
{
	//fread(&m_ItemType, sizeof(ITEM_TYPE), 1, _pFile);
}
