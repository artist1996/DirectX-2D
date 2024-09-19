#include "pch.h"
#include "CMonsterNextHPBarScript.h"

CMonsterNextHPBarScript::CMonsterNextHPBarScript()
	: CScript(SCRIPT_TYPE::MONSTERNEXTHPBARSCRIPT)
	, m_SegmentHP(100)
{
}

CMonsterNextHPBarScript::~CMonsterNextHPBarScript()
{
}

void CMonsterNextHPBarScript::Begin()
{
	Ptr<CTexture> pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\MonsterHUD\\MonsterHPBar0.png");
	m_vecTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\MonsterHUD\\MonsterHPBar1.png");
	m_vecTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\MonsterHUD\\MonsterHPBar2.png");
	m_vecTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\MonsterHUD\\MonsterHPBar3.png");
	m_vecTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\MonsterHUD\\MonsterHPBar4.png");
	m_vecTex.push_back(pTex);

	MeshRender()->GetDynamicMaterial();

	GetOwner()->SetActive(false);
}

void CMonsterNextHPBarScript::Tick()
{
	CGameObject* pTarget = GetOwner()->GetParent()->GetTarget();

	if (nullptr == pTarget)
		return;

	INFO& info = pTarget->GetInfo();

	Ptr<CTexture> pTex = CalculateHPBarTex(info.HP - static_cast<float>(m_SegmentHP));
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, pTex);
}

float CMonsterNextHPBarScript::CalculateRatio(float _TargetHP)
{
	return 0.0f;
}

Ptr<CTexture> CMonsterNextHPBarScript::CalculateHPBarTex(float _TargetHP)
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

	return m_vecTex[Idx % m_vecTex.size()];
}

void CMonsterNextHPBarScript::SaveToFile(FILE* _pFile)
{
}

void CMonsterNextHPBarScript::LoadFromFile(FILE* _pFile)
{
}
