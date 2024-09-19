#include "pch.h"
#include "CGatlinggunScript.h"

CGatlinggunScript::CGatlinggunScript()
	: CScript(SCRIPT_TYPE::GATLINGGUNSCRIPT)
	, m_Time(0.f)
	, m_UpDown(true)
{
}

CGatlinggunScript::~CGatlinggunScript()
{
}

void CGatlinggunScript::Begin()
{
	m_GatlinggunPistolPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gatlinggunpistol.pref");
	GetOwner()->SetActive(false);
}

void CGatlinggunScript::Tick()
{
	if (!GetOwner()->IsActive())
		return;

	if (L"Animation\\gatlinggunshoot\\gatlinggunshoot.anim" == Animator2D()->GetCurAnimation()->GetKey())
	{
		m_Time += DT;

		if (0.12f < m_Time)
		{
			CreatePistol();
			m_Time = 0.f;
		}
	}
}

void CGatlinggunScript::CreatePistol()
{
	Vec3 vPos = Transform()->GetWorldPos();
	CGameObject* pObject = m_GatlinggunPistolPref->Instantiate();
	if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetParent()->GetParent()->GetDir())
	{
		if(m_UpDown)
			pObject->Transform()->SetRelativePos(Vec3(vPos.x + 180.f, vPos.y + 100.f, vPos.z));
		else
			pObject->Transform()->SetRelativePos(Vec3(vPos.x + 180.f, vPos.y + 65.f, vPos.z));

		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.698132f));
		pObject->SetDir(OBJ_DIR::DIR_RIGHT);
	}
	else
	{
		if(m_UpDown)
			pObject->Transform()->SetRelativePos(Vec3(vPos.x - 180.f, vPos.y + 100.f, vPos.z));
		else
			pObject->Transform()->SetRelativePos(Vec3(vPos.x - 180.f, vPos.y + 65.f, vPos.z));

		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 2.391101f));
		pObject->SetDir(OBJ_DIR::DIR_LEFT);
	}

	if (m_UpDown)
		m_UpDown = false;
	else
		m_UpDown = true;

	CreateObject(pObject, 7);
}

void CGatlinggunScript::SaveToFile(FILE* _pFile)
{
}

void CGatlinggunScript::LoadFromFile(FILE* _pFile)
{
}