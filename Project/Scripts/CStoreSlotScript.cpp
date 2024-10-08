#include "pch.h"
#include "CStoreSlotScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CFontMgr.h>
#include "CMouseScript.h"

CStoreSlotScript::CStoreSlotScript()
	: CScript(SCRIPT_TYPE::STORESLOTSCRIPT)
	, m_Price(0)
	, m_Normal(true)
	, m_Hoverd(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Price", &m_Price);
	AddScriptParam(SCRIPT_PARAM::PREFAB, "Item", &m_ItemPref);
}

CStoreSlotScript::~CStoreSlotScript()
{
}

void CStoreSlotScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	Font();
}

void CStoreSlotScript::Tick()
{
	if (!GetOwner()->IsActive())
		return;

	MouseCheck();
	CheckHoved();
}

void CStoreSlotScript::Font()
{
	if (L"prefab\\BlackBraclet.pref" == m_ItemPref->GetKey())
	{
		GetOwner()->SetFont(L"��� : �������� �¾�");
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontOffset(Vec2(-45.f, -20.f));
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	}
	else if (L"prefab\\BlackNecklace.pref" == m_ItemPref->GetKey())
	{
		GetOwner()->SetFont(L"���� : �������� �¾�");
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontOffset(Vec2(-45.f, -20.f));
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	}
	else if (L"prefab\\BlackRing.pref" == m_ItemPref->GetKey())
	{
		GetOwner()->SetFont(L"�濰 : ��ĵǴ� �¾�");
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontOffset(Vec2(-45.f, -20.f));
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	}
	else if (L"prefab\\changcheonbelt.pref" == m_ItemPref->GetKey())
	{
		GetOwner()->SetFont(L"�� âõ�� ��� : ���Ա���");
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontOffset(Vec2(-45.f, -20.f));
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	}
	else if (L"prefab\\changcheoncoat.pref" == m_ItemPref->GetKey())
	{
		GetOwner()->SetFont(L"�� âõ�� ������ : ��������");
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontOffset(Vec2(-45.f, -20.f));
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	}
	else if (L"prefab\\changcheonneck.pref" == m_ItemPref->GetKey())
	{
		GetOwner()->SetFont(L"�� âõ�� Ǫ���� : ���б���");
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontOffset(Vec2(-45.f, -20.f));
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	}
	else if (L"prefab\\changcheonpants.pref" == m_ItemPref->GetKey())
	{
		GetOwner()->SetFont(L"�� âõ�� ���ٱ� : �Ȱ�����");
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontOffset(Vec2(-45.f, -20.f));
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	}
	else if (L"prefab\\changcheonshose.pref" == m_ItemPref->GetKey())
	{
		GetOwner()->SetFont(L"�� âõ�� ������ : �綼����");
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontOffset(Vec2(-45.f, -20.f));
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	}
	else if (L"prefab\\Weapon.pref" == m_ItemPref->GetKey())
	{
		GetOwner()->SetFont(L"��:��õ�� ����-������");
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontOffset(Vec2(-45.f, -20.f));
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	}
}

void CStoreSlotScript::MouseCheck()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vPos = Transform()->GetWorldPos();
	Vec3 vScale = Transform()->GetRelativeScale();

	if (vPos.x - vScale.x * 0.5f < vMousePos.x && vPos.x + vScale.x * 0.5f > vMousePos.x
		&& vPos.y + vScale.y * 0.5f > vMousePos.y && vPos.y - vScale.y * 0.5f < vMousePos.y)
	{
		CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
		CMouseScript* pMouseScript = static_cast<CMouseScript*>(pMouse->GetScripts()[0]);
		pMouseScript->SetClickInst(this);
		pMouseScript->SetClickDelegate((DELEGATE_0)&CStoreSlotScript::Buy);
		m_Hoverd = true;
	}
	else
	{
		CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
		CMouseScript* pMouseScript = static_cast<CMouseScript*>(pMouse->GetScripts()[0]);
		if (this == pMouseScript->GetLbtnInst())
		{
			pMouseScript->SetClickInst(nullptr);
			pMouseScript->SetClickDelegate(nullptr);
		}
		m_Hoverd = false;
	}
}

void CStoreSlotScript::CheckHoved()
{
	if (m_Hoverd)
	{
		GetOwner()->FindChildByName(L"Highlight")->SetActive(true);
	}
	else
	{
		GetOwner()->FindChildByName(L"Highlight")->SetActive(false);
	}
}

void CStoreSlotScript::Buy()
{
	CGameObject* pObj = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	INFO& info = pObj->GetInfo();

	// ��� �˻�
	if (info.iGold < m_Price)
		return;
	else
		info.iGold -= m_Price;

	const vector<CGameObject*>& vecChildrens = CLevelMgr::GetInst()->FindObjectByName(L"InventorySlotPanel")->GetChildren();

	for (size_t i = 0; i < vecChildrens.size(); ++i)
	{
		if (!vecChildrens[i]->GetChildren().empty())
			continue;
		
		CGameObject* pItem = m_ItemPref->Instantiate();
		CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(31, pItem);
		vecChildrens[i]->AddChild(pItem);

		break;
	}
}

void CStoreSlotScript::SaveToFile(FILE* _pFile)
{
	SaveAssetRef(m_ItemPref, _pFile);
	fwrite(&m_Price, sizeof(int), 1, _pFile);
}

void CStoreSlotScript::LoadFromFile(FILE* _pFile)
{
	LoadAssetRef(m_ItemPref, _pFile);
	fread(&m_Price, sizeof(int), 1, _pFile);
}