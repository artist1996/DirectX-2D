#include "pch.h"
#include "CMonsterHPBarScript.h"

CMonsterHPBarScript::CMonsterHPBarScript()
	: CScript(SCRIPT_TYPE::MONSTERHPBARSCRIPT)
	, m_Ratio(0.f)
	, m_SegmentHP(100)
{
}

CMonsterHPBarScript::~CMonsterHPBarScript()
{
}

void CMonsterHPBarScript::Begin()
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

void CMonsterHPBarScript::Tick()
{
	CGameObject* pTarget = GetOwner()->GetParent()->GetTarget();
	
	if (nullptr == pTarget)
		return;

	INFO& info = pTarget->GetInfo();

	CalculateRatio(info);
	MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, m_Ratio);
	Ptr<CTexture> pTex = CalculateHPBarTex(info.HP);
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, pTex);
}

void CMonsterHPBarScript::CalculateRatio(const INFO& _info)
{
	if (0.f < _info.HP)
	{
		float Divided = _info.HP / static_cast<float>(m_SegmentHP);

		if (Divided == (int)Divided)
			m_Ratio = 1.f;
		else
		{
			float Module = static_cast<int>(_info.HP) % m_SegmentHP;

			m_Ratio = Module / m_SegmentHP;
		}
	}
	else
		m_Ratio = 0.f;
}

Ptr<CTexture> CMonsterHPBarScript::CalculateHPBarTex(float _TargetHP)
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

	return m_vecTex[Idx % m_vecTex.size()];
}

void CMonsterHPBarScript::SaveToFile(FILE* _pFile)
{
}

void CMonsterHPBarScript::LoadFromFile(FILE* _pFile)
{
}