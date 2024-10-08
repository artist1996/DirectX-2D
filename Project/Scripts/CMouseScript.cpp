#include "pch.h"
#include "CMouseScript.h"
#include <Engine/CKeyMgr.h>

CMouseScript::CMouseScript()
	: CScript(SCRIPT_TYPE::MOUSESCRIPT)
	, m_ClickInst(nullptr)
	, m_ClickFunc(nullptr)
	, m_PressedInst(nullptr)
	, m_PressedFunc(nullptr)
	, m_RbtnClickInst(nullptr)
	, m_RbtnClickFunc(nullptr)
	, m_Click(false)
{
}

CMouseScript::~CMouseScript()
{
}

void CMouseScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
}

void CMouseScript::Tick()
{
	Vec2 vPos = CKeyMgr::GetInst()->GetMousePos();
	CGameObject* pTarget = GetOwner()->GetTarget();

	if (KEY_TAP(KEY::LBTN))
	{
		if (nullptr == m_ClickInst || nullptr == m_ClickFunc)
			return;
	
		(m_ClickInst->*m_ClickFunc)();
	}
	else if (KEY_PRESSED(KEY::LBTN))
	{
		if (nullptr == m_PressedInst || nullptr == m_PressedFunc)
			return;

		(m_PressedInst->*m_PressedFunc)();
	}

	if (KEY_TAP(KEY::RBTN))
	{
		if (nullptr == m_RbtnClickInst || nullptr == m_RbtnClickFunc)
			return;

		(m_RbtnClickInst->*m_RbtnClickFunc)();
	}

	Transform()->SetRelativePos(Vec3(vPos.x, vPos.y, 1.f));
}