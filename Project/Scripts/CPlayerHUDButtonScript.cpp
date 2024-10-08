#include "pch.h"
#include "CPlayerHUDButtonScript.h"

#include <Engine/CKeyMgr.h>
#include <Engine/CLevelMgr.h>

CPlayerHUDButtonScript::CPlayerHUDButtonScript()
	: CScript(SCRIPT_TYPE::PLAYERHUDBUTTONSCRIPT)
	, m_Type(HUD_TYPE::END)
	, m_Normal(true)
	, m_Hoverd(false)
	, m_Clicked(false)
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
	MouseCheck();

	if (m_Normal)
	{
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_NormalTex);
	}
	else if (m_Hoverd)
	{
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_HoverTex);
	}
	else if (m_Clicked)
	{
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_ClickTex);
	}
}

void CPlayerHUDButtonScript::MouseCheck()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vPos = Transform()->GetWorldPos();
	Vec3 vScale = Transform()->GetRelativeScale();

	if (vPos.x - vScale.x * 0.5f < vMousePos.x && vPos.x + vScale.x * 0.5f > vMousePos.x
		&& vPos.y + vScale.y * 0.5f > vMousePos.y && vPos.y - vScale.y * 0.5f < vMousePos.y)
	{
		m_Normal = false;
		m_Hoverd = true;
		//CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
		//pMouse->SetTarget(GetOwner());
	}
	else
	{
		m_Normal = true;
		m_Hoverd = false;
		//CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
		//pMouse->SetTarget(nullptr);
	}
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