#include "pch.h"
#include "CTapScript.h"
#include <Engine/CFontMgr.h>

CTapScript::CTapScript()
	: CScript(SCRIPT_TYPE::TAPSCRIPT)
	, m_Type(TAP_TYPE::END)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_Type);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Texture", &m_Tex);
}

CTapScript::~CTapScript()
{
}

void CTapScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_Tex);
	SetFont();
}

void CTapScript::Tick()
{
}

void CTapScript::SetFont()
{
	switch (m_Type)
	{
	case TAP_TYPE::EQUIPMENT:
		m_strFont = L"장비";
		GetOwner()->SetFont(m_strFont);
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
		GetOwner()->SetFontOffset(Vec2(-10.f, -5.f));
		break;
	case TAP_TYPE::CONSUMPTION:
		m_strFont = L"소모품";
		GetOwner()->SetFont(m_strFont);
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
		GetOwner()->SetFontOffset(Vec2(-13.f, -5.f));
		break;
	case TAP_TYPE::STUFF:
		m_strFont = L"재료";
		GetOwner()->SetFont(m_strFont);
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
		GetOwner()->SetFontOffset(Vec2(-10.f, -5.f));
		break;
	case TAP_TYPE::SPECIALITYMATERIALS:
		m_strFont = L"전문재료";
		GetOwner()->SetFont(m_strFont);
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
		GetOwner()->SetFontOffset(Vec2(-19.f, -5.f));
		break;
	case TAP_TYPE::QUEST:
		m_strFont = L"퀘스트";
		GetOwner()->SetFont(m_strFont);
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
		GetOwner()->SetFontOffset(Vec2(-14.f, -5.f));
		break;
	case TAP_TYPE::BUY:
		m_strFont = L"상점";
		GetOwner()->SetFont(m_strFont);
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
		GetOwner()->SetFontOffset(Vec2(-10.f, -5.f));
		break;
	case TAP_TYPE::REPURCHASE:
		m_strFont = L"재구매";
		GetOwner()->SetFont(m_strFont);
		GetOwner()->SetFontScale(10.f);
		GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
		GetOwner()->SetFontOffset(Vec2(-14.f, -5.f));
		break;
	}
}

void CTapScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Type, sizeof(TAP_TYPE), 1, _pFile);
	SaveAssetRef(m_Tex, _pFile);
}

void CTapScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Type, sizeof(TAP_TYPE), 1, _pFile);
	LoadAssetRef(m_Tex, _pFile);
}