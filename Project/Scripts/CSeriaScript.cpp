#include "pch.h"
#include "CSeriaScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CFontMgr.h>

#include "CMouseScript.h"

CSeriaScript::CSeriaScript()
	: CScript(SCRIPT_TYPE::SERIASCRIPT)
	, m_Active(true)
	, m_Time(0.f)
	, m_Prev(0)
{
}

CSeriaScript::~CSeriaScript()
{
}

void CSeriaScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	Animator2D()->Play(0, 5.f, true);

	//GetOwner()->SetFont(L"세리아 키르민");
	//GetOwner()->SetFontScale(13.f);
	//GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	//GetOwner()->SetFontOffset(Vec2(-28.f, -70.f));
}

void CSeriaScript::Tick()
{
	MouseCheck();
}

void CSeriaScript::MouseCheck()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 vPos = Transform()->GetWorldPos();
	Vec3 vScale = Transform()->GetRelativeScale();

	m_Time += DT;

	if (9.f < m_Time)
	{
		int Rand = CRandomMgr::GetInst()->GetRandom(3);
		m_Prev = Rand;

		if (Rand == m_Prev)
		{
			if (Rand == 0)
				Rand += 1;
			else
				Rand -= 1;
		}

		if (0 == Rand)
			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\seria\\seria_amb_01.ogg")->Play(1, 1.f, false);
		else if(1 == Rand)
			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\seria\\seria_amb_02.ogg")->Play(1, 1.f, false);
		else if(2 == Rand)
			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\seria\\seria_tk_03.ogg")->Play(1, 1.f, false);
		else if(3 == Rand)
			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\seria\\seria_fw_03.ogg")->Play(1, 1.f, false);

		m_Time = 0.f;
	}

	CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");


	if (nullptr == pMouse)
		return;

	CMouseScript* pMouseScript = static_cast<CMouseScript*>(pMouse->GetScripts()[0]);

	if (vPos.x - vScale.x * 0.5f < vMousePos.x && vPos.x + vScale.x * 0.5f > vMousePos.x
		&& vPos.y + vScale.y * 0.5f > vMousePos.y && vPos.y - vScale.y * 0.5f < vMousePos.y)
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_3, 1);
		MeshRender()->GetMaterial()->SetScalarParam(VEC4_1, Vec4(0.f, 1.f, 0.f, 1.f));
		pMouseScript->SetClickInst(this);
		pMouseScript->SetClickDelegate((DELEGATE_0)&CSeriaScript::Click);
	}
	else
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_3, 0);
		if (this == pMouseScript->GetLbtnInst())
		{
			pMouseScript->SetClickInst(nullptr);
			pMouseScript->SetClickDelegate(nullptr);
		}
		//CGameObject* pMouse = CLevelMgr::GetInst()->FindObjectByName(L"Mouse");
		//pMouse->SetTarget(nullptr);
	}
}

void CSeriaScript::Click()
{
	CLevelMgr::GetInst()->FindObjectByName(L"StorePanel")->SetActive(m_Active);
	m_Active = !m_Active;

	if(!m_Active)
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\seria\\seria_tk_02.ogg")->Play(1, 1.f, false);
	else
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\seria\\seria_amb_03.ogg")->Play(1, 1.f, false);
}

void CSeriaScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}