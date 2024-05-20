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
	// ī�޶� ���
	if (-1 != m_Priority)
	{
		CRenderMgr::GetInst()->RegisterCamera(this, m_Priority);
	}
}

void CCamera::FinalTick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	// View Space �� ī�޶� ��ǥ���� ������ �Ǵ� ��ǥ��
	// 1. ī�޶� ������ ����
	// 2. ī�޶� �ٶ󺸴� ������ Z ��	
	
	// View ����� ����Ѵ�.
	// View ����� World Space -> View Space �� �����Ҷ� ����ϴ� ���
	
	m_matView = XMMatrixTranslation(-Transform()->GetRelativePos().x, -Transform()->GetRelativePos().y, -Transform()->GetRelativePos().z);

	// Projection Space ���� ��ǥ��(NDC)
	// 1. ���� ���� (Orthographic)
	// ������ ����������
	// �þ� ������ NDC �� ����
	m_matProj = XMMatrixOrthographicLH(m_Width, m_Height, 1.f, 10000.f);

	// 2. ���� ���� (Perspective)

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