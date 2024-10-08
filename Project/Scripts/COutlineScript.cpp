#include "pch.h"
#include "COutlineScript.h"

COutlineScript::COutlineScript()
	: CScript(SCRIPT_TYPE::OUTLINESCRIPT)
{
}

COutlineScript::~COutlineScript()
{
}

void COutlineScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetScalarParam(INT_2, 1);
}

void COutlineScript::Tick()
{
	MouseCheck();
}

void COutlineScript::MouseCheck()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vPos = Transform()->GetWorldPos();
	Vec3 vScale = Transform()->GetRelativeScale();

	if (vPos.x - vScale.x * 0.5f < vMousePos.x && vPos.x + vScale.x * 0.5f > vMousePos.x
		&& vPos.y + vScale.y * 0.5f > vMousePos.y && vPos.y - vScale.y * 0.5f < vMousePos.y)
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_3, 1);
		MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_1, Vec4(0.f, 1.f, 0.f, 1.f));
		MeshRender()->GetMaterial()->SetTexParam(TEX_0, GetOwner()->GetParent()->Animator2D()->GetCurSprite()->GetAtlasTexture());
		//CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
		//pMouse->SetTarget(GetOwner());
	}
	else
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_3, 0);
		MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_1, Vec4(0.f, 0.f, 0.f, 0.f));
		MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
		//CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
		//pMouse->SetTarget(nullptr);
	}
}