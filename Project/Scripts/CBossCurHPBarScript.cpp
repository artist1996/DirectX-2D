#include "pch.h"
#include "CBossCurHPBarScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CFontMgr.h>

CBossCurHPBarScript::CBossCurHPBarScript()
	: CScript(SCRIPT_TYPE::BOSSCURHPBARSCRIPT)
	, m_Target(nullptr)
	, m_SegmentHP(100)
	, m_HPRatio(0.f)
{
	//MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\bosshud\\BossHPBar3.png"));
}

CBossCurHPBarScript::~CBossCurHPBarScript()
{
}

void CBossCurHPBarScript::Begin()
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

	GetOwner()->SetFont(L"LV110 보스-검은 질병의 디레지에");
	GetOwner()->SetFontScale(13.f);
	GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	GetOwner()->SetFontOffset(Vec2(0.f, -50.f));
}

void CBossCurHPBarScript::Tick()
{
	INFO& info = m_Target->GetInfo();
	m_HPRatio = CalculateRatio(info.HP);

	static float currentHP = info.HP;
	currentHP = Lerp(currentHP, info.HP, 0.01f);

	Ptr<CTexture> pTex = CalculateHPBarTex(currentHP);

	MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, CalculateRatio(currentHP));
	MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

	CGameObject* pObject = CLevelMgr::GetInst()->FindObjectByName(L"MainCamera");

	Vec3 vPos = pObject->Transform()->GetRelativePos() - Transform()->GetRelativePos();

	GetOwner()->SetFontOffset(Vec2(vPos.x - 242.f, -50.f));
}

float CBossCurHPBarScript::Lerp(float _start, float _end, float _t)
{
	return _start + (_end - _start) * _t;
}

float CBossCurHPBarScript::CalculateRatio(float _TargetHP)
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

Ptr<CTexture> CBossCurHPBarScript::CalculateHPBarTex(float _TargetHP)
{
	int Idx = 0;

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

void CBossCurHPBarScript::SaveToFile(FILE* _pFile)
{
}

void CBossCurHPBarScript::LoadFromFile(FILE* _pFile)
{
}