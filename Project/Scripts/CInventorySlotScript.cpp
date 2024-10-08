#include "pch.h"
#include "CInventorySlotScript.h"

CInventorySlotScript::CInventorySlotScript()
	: CScript(SCRIPT_TYPE::INVENTORYSLOTSCRIPT)
	, m_Normal(true)
	, m_Hoverd(false)
{
}

CInventorySlotScript::~CInventorySlotScript()
{
}

void CInventorySlotScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	m_NormalTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\inventory\\InventorySlot.png");
	m_HoverTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\inventory\\InventorySlotHover.png");
}

void CInventorySlotScript::Tick()
{
	if (!GetOwner()->IsActive())
		return;

	MouseCheck();

	if (m_Normal)
	{
		MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_NormalTex);
	}
	else if(m_Hoverd)
	{
		MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_HoverTex);
	}
}

void CInventorySlotScript::MouseCheck()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vPos = Transform()->GetWorldPos();
	Vec3 vScale = Transform()->GetRelativeScale();

	if (vPos.x - vScale.x * 0.5f < vMousePos.x && vPos.x + vScale.x * 0.5f > vMousePos.x
		&& vPos.y + vScale.y * 0.5f > vMousePos.y && vPos.y - vScale.y * 0.5f < vMousePos.y)
	{
		m_Normal = false;
		m_Hoverd = true;
	}
	else
	{
		m_Normal = true;
		m_Hoverd = false;
	}
}