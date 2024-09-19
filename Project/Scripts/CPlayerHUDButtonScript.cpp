#include "pch.h"
#include "CPlayerHUDButtonScript.h"

CPlayerHUDButtonScript::CPlayerHUDButtonScript()
	: CScript(SCRIPT_TYPE::PLAYERHUDBUTTONSCRIPT)
	, m_Type(HUD_TYPE::END)
{
	//m_NormalTex = CAssetMgr::GetInst()->FindAsset<CTexture>();
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_Type);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Normal", &m_NormalTex);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Hover", &m_HoverTex);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Click", &m_ClickTex);
}

CPlayerHUDButtonScript::~CPlayerHUDButtonScript()
{
}

void CPlayerHUDButtonScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
}

void CPlayerHUDButtonScript::Tick()
{
	MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_NormalTex);
}

void CPlayerHUDButtonScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Type, sizeof(HUD_TYPE), 1, _pFile);
	SaveAssetRef(m_NormalTex, _pFile);
	SaveAssetRef(m_HoverTex, _pFile);
	SaveAssetRef(m_ClickTex, _pFile);
}

void CPlayerHUDButtonScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Type, sizeof(HUD_TYPE), 1, _pFile);
	LoadAssetRef(m_NormalTex, _pFile);
	LoadAssetRef(m_HoverTex, _pFile);
	LoadAssetRef(m_ClickTex, _pFile);
}