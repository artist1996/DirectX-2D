#include "pch.h"
#include "CMonsterHPFontScript.h"

CMonsterHPFontScript::CMonsterHPFontScript()
	: CScript(SCRIPT_TYPE::MONSTERHPFONTSCRIPT)
	, m_pTarget(nullptr)
	, m_Ratio(0)
{
}

CMonsterHPFontScript::~CMonsterHPFontScript()
{
}

void CMonsterHPFontScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	m_strPath = L"texture\\MonsterDigit\\Digit";

	GetOwner()->SetActive(false);
}

void CMonsterHPFontScript::Tick()
{
	m_pTarget = GetOwner()->GetParent()->GetTarget();

	if (nullptr == m_pTarget)
		return;

	INFO& info = m_pTarget->GetInfo();
	CalculateRatio(info);
	SetTexture();
}

void CMonsterHPFontScript::CalculateRatio(INFO& _info)
{
	if(L"hyungteo" == m_pTarget->GetName())
		m_Ratio = static_cast<int>((_info.HP / _info.MaxHP) * 25);
	else if(L"juris" == m_pTarget->GetName())
		m_Ratio = static_cast<int>((_info.HP / _info.MaxHP) * 27);
	else if(L"meltknight" == m_pTarget->GetName())
		m_Ratio = static_cast<int>((_info.HP / _info.MaxHP) * 6);
}

void CMonsterHPFontScript::SetTexture()
{
	if (0 == m_Ratio)
		m_Ratio = 1;

	const wstring& string = to_wstring(m_Ratio);

	MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(m_strPath + string + L".png"));
}

void CMonsterHPFontScript::SaveToFile(FILE* _pFile)
{
}

void CMonsterHPFontScript::LoadFromFile(FILE* _pFile)
{
}