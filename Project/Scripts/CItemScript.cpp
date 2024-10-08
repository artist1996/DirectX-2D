#include "pch.h"
#include "CItemScript.h"

#include <Engine/CLevelMgr.h>
#include "CMouseScript.h"

CItemScript::CItemScript()
	: CScript(SCRIPT_TYPE::ITEMSCRIPT)
	, m_Equip(false)
	, m_Type(ITEM_TYPE::END)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Item Type", &m_Type);
}

CItemScript::~CItemScript()
{
}

void CItemScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
}

void CItemScript::Tick()
{
	if (!GetOwner()->IsActive())
		return;

	MouseCheck();
}

void CItemScript::MouseCheck()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vPos = Transform()->GetWorldPos();
	Vec3 vScale = Transform()->GetRelativeScale();

	if (vPos.x - vScale.x * 0.5f < vMousePos.x && vPos.x + vScale.x * 0.5f > vMousePos.x
		&& vPos.y + vScale.y * 0.5f > vMousePos.y && vPos.y - vScale.y * 0.5f < vMousePos.y)
	{
		CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
		CMouseScript* pMouseScript = static_cast<CMouseScript*>(pMouse->GetScripts()[0]);
		if (m_Equip)
		{
			pMouseScript->SetRbtnClickInst(this);
			pMouseScript->SetRbtnClickDelegate((DELEGATE_2)&CItemScript::UnEquipment);
		}
		else
		{
			pMouseScript->SetRbtnClickInst(this);
			pMouseScript->SetRbtnClickDelegate((DELEGATE_2)&CItemScript::Equipment);
		}
	}
	else
	{
		CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
		CMouseScript* pMouseScript = static_cast<CMouseScript*>(pMouse->GetScripts()[0]);
		if (this == pMouseScript->GetRbtnInst())
		{
			pMouseScript->SetRbtnClickInst(nullptr);
			pMouseScript->SetRbtnClickDelegate(nullptr);
		}
	}
}

void CItemScript::Equipment()
{
	CGameObject* pObj = nullptr;

	switch (m_Type)
	{
	case ITEM_TYPE::WEAPON:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"WeaponSlot");
	}
	break;
	case ITEM_TYPE::COAT:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"CoatSlot");
	}
	break;
	case ITEM_TYPE::PANTS:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"PantsSlot");
	}
	break;
	case ITEM_TYPE::SHOULDER:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"ShoulderSlot");
	}
	break;
	case ITEM_TYPE::SHOES:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"ShoseSlot");
	}
	break;
	case ITEM_TYPE::BELT:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"BeltSlot");
	}
	break;
	case ITEM_TYPE::RING:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"RingSlot");
	}
	break;
	case ITEM_TYPE::NECKLACE:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"NecklaceSlot");
	}
	break;
	case ITEM_TYPE::BRACELET:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"BracletSlot");
	}
	break;
	case ITEM_TYPE::EARRING:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"EaringSlot");
	}
	break;
	case ITEM_TYPE::MAGICSTONE:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"MagicStoneSlot");
	}
	break;
	case ITEM_TYPE::ASSISTANCE:
	{
		pObj = CLevelMgr::GetInst()->FindObjectByName(L"AssistanceSlot");
	}
	break;
	}

	if (pObj->GetChildren().empty())
	{
		pObj->AddChild(GetOwner());
		m_Equip = true;
		Sound();
	}
	else
	{
		CGameObject* pChild = pObj->GetChildren()[0];
		static_cast<CItemScript*>(pChild->GetScripts()[0])->SetEquip(false);
		CGameObject* pParent = GetOwner()->GetParent();
		pParent->AddChild(pChild);
		static_cast<CItemScript*>(GetOwner()->GetScripts()[0])->SetEquip(true);
		pObj->AddChild(GetOwner());
		Sound();
	}
}

void CItemScript::UnEquipment()
{
	CGameObject* pObj = CLevelMgr::GetInst()->FindObjectByName(L"InventorySlotPanel");

	const vector<CGameObject*> vecChild = pObj->GetChildren();
	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		if (!vecChild[i]->GetChildren().empty())
			continue;

		vecChild[i]->AddChild(GetOwner());
		m_Equip = false;
		break;
	}
}

void CItemScript::Sound()
{
	if (ITEM_TYPE::RING == m_Type)
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\equipment\\ring.ogg")->Play(1, 1.f, false);
	else if(ITEM_TYPE::NECKLACE == m_Type)
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\equipment\\necklace.ogg")->Play(1, 1.f, false);
	else if(ITEM_TYPE::BRACELET == m_Type)
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\equipment\\bracelet.ogg")->Play(1, 1.f, false);
	else
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\equipment\\assist_touch.ogg")->Play(1, 1.f, true);
}

void CItemScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Type, sizeof(ITEM_TYPE), 1, _pFile);
}

void CItemScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Type, sizeof(ITEM_TYPE), 1, _pFile);
}
