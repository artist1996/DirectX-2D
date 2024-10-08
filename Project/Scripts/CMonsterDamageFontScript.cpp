#include "pch.h"
#include "CMonsterDamageFontScript.h"

CMonsterDamageFontScript::CMonsterDamageFontScript()
	: CScript(SCRIPT_TYPE::MONSTERDAMAGEFONTSCRIPT)
	, m_Type(FONT_TYPE::END)
	, m_Time(0.f)
	, m_Damage(0)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_Type);
}

CMonsterDamageFontScript::~CMonsterDamageFontScript()
{
}

void CMonsterDamageFontScript::Begin()
{
	const vector<CGameObject*> vecChildren = GetOwner()->GetChildren();

	wstring strPath;
	if (FONT_TYPE::NORMAL == m_Type)
		strPath = L"texture\\monsterhit\\normal\\normalhitfont0";
	else
		strPath = L"texture\\monsterhit\\critical\\criticalhitfont0";

	m_strFont = to_wstring(m_Damage);

	for (size_t i = 0; i < m_strFont.size(); ++i)
	{
		vecChildren[i]->MeshRender()->GetDynamicMaterial();
		Ptr<CTexture> pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(strPath + m_strFont[i] + L".png");
		vecChildren[i]->MeshRender()->GetMaterial()->SetTexParam(TEX_0, pTex);
	}
}

void CMonsterDamageFontScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	m_Time += DT;

	if (0.5f < m_Time)
		DeleteObject(GetOwner());

	vPos += Vec3(0.f, 1.f, 0.f) * 100.f * DT;

	Transform()->SetRelativePos(vPos);
}

void CMonsterDamageFontScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Type, sizeof(FONT_TYPE), 1, _pFile);
}

void CMonsterDamageFontScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Type, sizeof(FONT_TYPE), 1, _pFile);
}
