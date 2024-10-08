#include "pch.h"
#include "CStorePriceScript.h"

#include <Engine/CFontMgr.h>
#include "CStoreSlotScript.h"

CStorePriceScript::CStorePriceScript()
	: CScript(SCRIPT_TYPE::STOREPRICESCRIPT)
{
}

CStorePriceScript::~CStorePriceScript()
{
}

void CStorePriceScript::Begin()
{
	MeshRender()->GetDynamicMaterial();

	wchar_t szBuff[255] = {};

	int Price = static_cast<CStoreSlotScript*>(GetOwner()->GetParent()->GetScripts()[0])->GetPrice();

	swprintf_s(szBuff, L"%d", Price);

	m_strFont = szBuff;

	GetOwner()->SetFont(m_strFont);
	GetOwner()->SetFontScale(13.f);
	GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	GetOwner()->SetFontOffset(Vec2(30.f, -7.f));
}

void CStorePriceScript::Tick()
{
}