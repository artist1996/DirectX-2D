#include "pch.h"
#include "CPanelScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CFontMgr.h>
#include "CMouseScript.h"

CPanelScript::CPanelScript()
	: CScript(SCRIPT_TYPE::PANELSCRIPT)
	, m_Active(false)
{
}

CPanelScript::~CPanelScript()
{
}

void CPanelScript::Begin()
{
	GetOwner()->SetActive(m_Active);

	if(L"MainPanel" == GetOwner()->GetName())
	{
		GetOwner()->SetFont(L"장비 인벤토리(I)");
		GetOwner()->SetFontOffset(Vec2(-45.f, -10.f));
		GetOwner()->SetFontScale(13.f);
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	}
}

void CPanelScript::Tick()
{
	ShortCut();

	if (!GetOwner()->IsActive())
		return;

	MouseCheck();
}

void CPanelScript::MouseCheck()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vPos = Transform()->GetWorldPos();
	Vec3 vScale = Transform()->GetRelativeScale();

	if (vPos.x - vScale.x * 0.5f < vMousePos.x && vPos.x + vScale.x * 0.5f > vMousePos.x
		&& vPos.y + vScale.y * 0.5f > vMousePos.y && vPos.y - vScale.y * 0.5f < vMousePos.y)
	{
		if (L"MainPanel" == GetOwner()->GetName())
		{
			CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
			CMouseScript* pMouseScript = static_cast<CMouseScript*>(pMouse->GetScripts()[0]);
			pMouseScript->SetClickInst(this);
			pMouseScript->SetClickDelegate((DELEGATE_0)&CPanelScript::Click);
			pMouseScript->SetPressedInst(this);
			pMouseScript->SetPressedDelegate((DELEGATE_1)&CPanelScript::Move);
		}
	}
	else
	{
		CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
		CMouseScript* pMouseScript = static_cast<CMouseScript*>(pMouse->GetScripts()[0]);
		if (this == pMouseScript->GetLbtnInst())
		{
			pMouseScript->SetClickInst(nullptr);
			pMouseScript->SetClickDelegate(nullptr);
			pMouseScript->SetPressedInst(nullptr);
			pMouseScript->SetPressedDelegate(nullptr);
		}
	}
}

void CPanelScript::ShortCut()
{
	if (KEY_TAP(KEY::I))
	{
		GetOwner()->SetActive(m_Active);
		m_Active = !m_Active;
	}
}

void CPanelScript::Click()
{
	m_ClickPos = Transform()->GetRelativePos();
}

void CPanelScript::Move()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vCurMousePos = Vec3(CKeyMgr::GetInst()->GetMousePos().x, CKeyMgr::GetInst()->GetMousePos().y, 1.f);

	Vec3 vDiff = vCurMousePos - m_ClickPos;

	Vec3 vNextPos = vPos + vDiff;

	Transform()->SetRelativePos(vNextPos);

	m_ClickPos = vCurMousePos;
}