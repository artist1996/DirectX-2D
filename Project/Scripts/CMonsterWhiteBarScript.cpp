#include "pch.h"
#include "CMonsterWhiteBarScript.h"

CMonsterWhiteBarScript::CMonsterWhiteBarScript()
	: CScript(SCRIPT_TYPE::MONSTERWHITEBARSCRIPT)
	, m_SegmentHP(100)
	, m_HPRatio(0.f)
{
}

CMonsterWhiteBarScript::~CMonsterWhiteBarScript()
{
}

void CMonsterWhiteBarScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\MonsterHUD\\MonsterWhiteBar.png"));
	GetOwner()->SetActive(false);
}

void CMonsterWhiteBarScript::Tick()
{
	CGameObject* pTarget = GetOwner()->GetParent()->GetTarget();

	if (nullptr == pTarget)
		return;

	INFO& info = pTarget->GetInfo();

	static float currentHP = info.HP;

	currentHP = Lerp(currentHP, info.HP, 0.03f);

    CalculateRatio(currentHP);
	MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, CalculateRatio(currentHP));
}

float CMonsterWhiteBarScript::Lerp(float _start, float _end, float _t)
{
	return _start + (_end - _start) * _t;
}

float CMonsterWhiteBarScript::CalculateRatio(float _TargetHP)
{
	float ResultRatio = 0.f;

	if (0.f < _TargetHP)
	{
		float Divided = _TargetHP / static_cast<float>(m_SegmentHP);

		if (Divided == (int)Divided)
			ResultRatio = 1.f;
		else
		{
			float Module = static_cast<int>(_TargetHP) % m_SegmentHP;

			ResultRatio = Module / m_SegmentHP;
		}
	}
	else
		ResultRatio = 0.f;

	return ResultRatio;
}

void CMonsterWhiteBarScript::SaveToFile(FILE* _pFile)
{
}

void CMonsterWhiteBarScript::LoadFromFile(FILE* _pFile)
{
}
