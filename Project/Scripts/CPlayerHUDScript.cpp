#include "pch.h"
#include "CPlayerHUDScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CFontMgr.h>

CPlayerHUDScript::CPlayerHUDScript()
	: CScript(SCRIPT_TYPE::PLAYERHUDSCRIPT)
	, m_pTarget(nullptr)
	, m_Ratio(0.f)
{
}

CPlayerHUDScript::~CPlayerHUDScript()
{
}

void CPlayerHUDScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	m_pTarget = CLevelMgr::GetInst()->FindObjectByName(L"Player");
}

void CPlayerHUDScript::Tick()
{
	if (nullptr == m_pTarget)
		return;

	INFO& info = m_pTarget->GetInfo();

	CalculateByRatio(info);

	MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, m_Ratio);
	//if(L"PlayerHP" == GetOwner()->GetName())
	//	Font();
}

void CPlayerHUDScript::CalculateByRatio(INFO& _info)
{
	m_Ratio = _info.HP / _info.MaxHP;
}

void CPlayerHUDScript::Font()
{
	Vec3 vPos = Transform()->GetWorldPos();
	Vec3 vCamPos = CLevelMgr::GetInst()->FindObjectByName(L"MainCamera")->Transform()->GetWorldPos();

	Vec3 vDist = vCamPos - vPos;
	int Ratio = int(m_Ratio * 100.f);
	wstring Font = to_wstring(Ratio);
	Font += L"%";
	GetOwner()->SetFont(Font);
	GetOwner()->SetFontScale(12.f);
	GetOwner()->SetFontColor(FONT_RGBA(248, 99, 0, 255));
	GetOwner()->SetFontOffset(Vec2(vDist.x - 365.f, -47.f));
}

void CPlayerHUDScript::SaveToFile(FILE* _pFile)
{
}

void CPlayerHUDScript::LoadFromFile(FILE* _pFile)
{
}