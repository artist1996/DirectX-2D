#include "pch.h"
#include "CStorePanelScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CFontMgr.h>
#include "CMouseScript.h"

CStorePanelScript::CStorePanelScript()
	: CScript(SCRIPT_TYPE::STOREPANELSCRIPT)
{
}

CStorePanelScript::~CStorePanelScript()
{
}

void CStorePanelScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	GetOwner()->SetActive(false);
	GetOwner()->SetFont(L"세리아 키르민");
	GetOwner()->SetFontScale(13.f);
	GetOwner()->SetFontOffset(Vec2(-40.f, -10.f));
	GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
}

void CStorePanelScript::Tick()
{
	if (!GetOwner()->IsActive())
		return;

	MouseCheck();
}

void CStorePanelScript::MouseCheck()
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
		pMouseScript->SetClickDelegate((DELEGATE_0)&CStorePanelScript::Click);
		pMouseScript->SetPressedInst(this);
		pMouseScript->SetPressedDelegate((DELEGATE_1)&CStorePanelScript::Move);
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

void CStorePanelScript::Click()
{
	m_ClickPos = Transform()->GetRelativePos();
}

void CStorePanelScript::Move()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vCurMousePos = Vec3(CKeyMgr::GetInst()->GetMousePos().x, CKeyMgr::GetInst()->GetMousePos().y, 1.f);

	Vec3 vDiff = vCurMousePos - m_ClickPos;

	Vec3 vNextPos = vPos + vDiff;

	Transform()->SetRelativePos(vNextPos);

	m_ClickPos = vCurMousePos;
}