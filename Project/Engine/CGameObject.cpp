#include "pch.h"
#include "CGameObject.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CComponent.h"
#include "CTransform.h"
#include "CRenderComponent.h"


CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::AddComponent(CComponent* _Component)
{
	COMPONENT_TYPE Type = _Component->GetComponentType();

	assert(nullptr == m_arrCom[(UINT)Type]);
	
	m_arrCom[(UINT)Type] = _Component;
	m_arrCom[(UINT)Type]->SetOwner(this);

	CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Component);
	
	assert(!(pRenderCom && m_RenderCom));

	if(pRenderCom)
		m_RenderCom = pRenderCom;
}

void CGameObject::Begin()
{
}

void CGameObject::Tick()
{
	float fDT = CTimeMgr::GetInst()->GetDeltaTime();
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT))
	{
		vPos.x += fDT * 1.f;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::LEFT))
	{
		vPos.x -= fDT * 1.f;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::UP))
	{
		vPos.y += fDT * 1.f;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::DOWN))
	{
		vPos.y -= fDT * 1.f;
	}

	Transform()->SetRelativePos(vPos);
}

void CGameObject::FinalTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->FinalTick();
	}
}

void CGameObject::Render()
{
	if(m_RenderCom)
		m_RenderCom->Render();
}