#include "pch.h"
#include "CBossNextHPBarScript.h"

#include <Engine/CLevelMgr.h>

CBossNextHPBarScript::CBossNextHPBarScript()
	: CScript(SCRIPT_TYPE::BOSSNEXTHPBARSCRIPT)
	, m_Target(nullptr)
	, m_SegmentHP(100)
{
}

CBossNextHPBarScript::~CBossNextHPBarScript()
{
}

void CBossNextHPBarScript::Begin()
{
	m_Target = CLevelMgr::GetInst()->FindObjectByName(L"direzie");
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\bosshud\\BossHPBar0.png");
	m_vecHPBarTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\bosshud\\BossHPBar1.png");
	m_vecHPBarTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\bosshud\\BossHPBar2.png");
	m_vecHPBarTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\bosshud\\BossHPBar3.png");
	m_vecHPBarTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\bosshud\\BossHPBar4.png");
	m_vecHPBarTex.push_back(pTex);
}

void CBossNextHPBarScript::Tick()
{
	INFO& info = m_Target->GetInfo();

	Ptr<CTexture> pTex = CalculateHPBarTex(info.HP - static_cast<float>(m_SegmentHP));
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, pTex);
}

float CBossNextHPBarScript::CalculateRatio(float _TargetHP)
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

Ptr<CTexture> CBossNextHPBarScript::CalculateHPBarTex(float _TargetHP)
{
	int Idx = 0;

	if (0.f >= _TargetHP)
		return nullptr;

	if (0.f < _TargetHP)
	{
		float Divided = _TargetHP / static_cast<float>(m_SegmentHP);

		Idx = static_cast<int>(Divided);

		if (Divided == (int)Divided)
		{
			--Idx;
		}
	}

	return m_vecHPBarTex[Idx % m_vecHPBarTex.size()];
}

void CBossNextHPBarScript::SaveToFile(FILE* _pFile)
{
}

void CBossNextHPBarScript::LoadFromFile(FILE* _pFile)
{
}