#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"
#include "CRenderMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"

#include "CTransform.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_Priority(-1)
	, m_LayerCheck(0)
	, m_Width(0.f)
	, m_Height(0.f)
{
	Vec2 vResolution = CDevice::GetInst()->GetResolution();
	m_Width = vResolution.x;
	m_Height = vResolution.y;
}

CCamera::~CCamera()
{
}

void CCamera::Begin()
{
	// 카메라 등록
	if (-1 != m_Priority)
	{
		CRenderMgr::GetInst()->RegisterCamera(this, m_Priority);
	}
}

void CCamera::FinalTick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	// View Space 란 카메라가 좌표계의 기준이 되는 좌표계
	// 1. 카메라가 원점에 존재
	// 2. 카메라가 바라보는 방향이 Z 축	
	
	// View 행렬을 계산한다.
	// View 행렬은 World Space -> View Space 로 변경할때 사용하는 행렬
	
	m_matView = XMMatrixTranslation(-Transform()->GetRelativePos().x, -Transform()->GetRelativePos().y, -Transform()->GetRelativePos().z);

	// Projection Space 투영 좌표계(NDC)
	// 1. 직교 투영 (Orthographic)
	// 투영을 일직선으로
	// 시야 범위를 NDC 로 압축
	m_matProj = XMMatrixOrthographicLH(m_Width, m_Height, 1.f, 10000.f);

	// 2. 원근 투영 (Perspective)

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x += 100.f * DT;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x -= 100.f * DT;
	}

	Transform()->SetRelativePos(vPos);
}

void CCamera::Render()
{
	g_Trans.matView = m_matView;
	g_Trans.matProj = m_matProj;

	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pLevel->GetLayer(i);

		const vector<CGameObject*>& vecObjects = pLayer->GetParentObjects();
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			vecObjects[j]->Render();
		}
	}
}