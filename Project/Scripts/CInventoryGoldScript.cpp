#include "pch.h"
#include "CInventoryGoldScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CFontMgr.h>

CInventoryGoldScript::CInventoryGoldScript()
	: CScript(SCRIPT_TYPE::INVENTORYGOLDSCRIPT)
	, m_pTarget(nullptr)
{
}

CInventoryGoldScript::~CInventoryGoldScript()
{
}

void CInventoryGoldScript::Begin()
{
	m_pTarget = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	GetOwner()->SetFontScale(15.f);
	GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	GetOwner()->SetFontOffset(Vec2(70.f, -7.f));
}

void CInventoryGoldScript::Tick()
{
	if (nullptr == m_pTarget)
		return;

	INFO& info = m_pTarget->GetInfo();

	wchar_t szBuff[255] = {};
	swprintf_s(szBuff, L"%d", info.iGold);

	m_strFont = szBuff;

	GetOwner()->SetFont(m_strFont);
}