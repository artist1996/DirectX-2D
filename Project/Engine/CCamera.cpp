#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"
#include "CRenderMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"

#include "CRenderComponent.h"

#include "CTransform.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_Priority(-1)
	, m_LayerCheck(0)
	, m_ProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_Width(0.f)
	, m_Height(0.f)
	, m_Far(100000.f)
	, m_FOV(XM_PI / 2.f)
	, m_ProjectionScale(1.f)
	, m_AspectRatio(0.f)
	, m_ZoomIn(false)
	, m_ZoomOut(false)
	, m_ShakingIn(false)
	, m_ShakingOut(false)
	, m_UI(false)
{
	Vec2 vResolution = CDevice::GetInst()->GetResolution();
	m_Width = vResolution.x;
	m_Height = vResolution.y;
	m_AspectRatio = m_Width / m_Height;
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
	
	Matrix matTrans = XMMatrixTranslation(-Transform()->GetRelativePos().x, -Transform()->GetRelativePos().y, -Transform()->GetRelativePos().z);
	Matrix matRot;
	Vec3 vR = Transform()->GetWorldDir(DIR::RIGHT);
	Vec3 vU = Transform()->GetWorldDir(DIR::UP);
	Vec3 vF = Transform()->GetWorldDir(DIR::FRONT);

	// ��ġ
	matRot._11 = vR.x; matRot._12 = vU.x; matRot._13 = vF.x;
	matRot._21 = vR.y; matRot._22 = vU.y; matRot._23 = vF.y;
	matRot._31 = vR.z; matRot._32 = vU.z; matRot._33 = vF.z;

	m_matView = matTrans * matRot;

	if (m_ZoomIn)
	{
		ZoomIn();
	}

	else if (m_ZoomOut)
	{
		ZoomOut();
	}

	if (m_ShakingIn)
	{
		ShakingIn();
	}

	else if (m_ShakingOut)
	{
		ShakingOut();
	}
	
	// Projection Space ���� ��ǥ��(NDC)
	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		// 1. ���� ���� (Orthographic)
		// ������ ����������
		// �þ� ������ NDC �� ����
		m_matProj = XMMatrixOrthographicLH(m_Width * m_ProjectionScale, m_Height * m_ProjectionScale, 1.f, m_Far);
	}

	else
	{
		// 2. ���� ���� (Perspective)
		// ��Ⱦ��(Ratio)
		m_matProj = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, 1.f, m_Far);
	}
}

void CCamera::SortGameObject()
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (false == (m_LayerCheck & (1 << i)))
		{
			continue;
		}

		CLayer* pLayer = pLevel->GetLayer(i);

		const vector<CGameObject*>& vecObjects = pLayer->GetObjects();

				
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			if (nullptr == vecObjects[j]->GetRenderComponent()
			 || nullptr == vecObjects[j]->GetRenderComponent()->GetMesh()
			 || nullptr == vecObjects[j]->GetRenderComponent()->GetMaterial()
			 || nullptr == vecObjects[j]->GetRenderComponent()->GetMaterial()->GetShader())
			{
				continue;
			}
			
			Ptr<CGraphicShader> pShader = vecObjects[j]->GetRenderComponent()->GetMaterial()->GetShader();
			SHADER_DOMAIN Domain = pShader->GetDomain();
			
			switch (Domain)
			{
			case DOMAIN_OPAQUE:
				m_vecOpaque.push_back(vecObjects[j]);
				break;
			case DOMAIN_MASKED:
				m_vecMasked.push_back(vecObjects[j]);
				break;
			case DOMAIN_TRANSPARENT:
				m_vecTransparent.push_back(vecObjects[j]);
				break;
			case DOMAIN_PARTICLE:
				m_vecParticles.push_back(vecObjects[j]);
				break;
			case DOMAIN_POSTPROCESS:
				m_vecPostProcess.push_back(vecObjects[j]);
				break;
			case DOMAIN_UI:
				m_vecUI.push_back(vecObjects[j]);
				break;
			}
		}
	}
}

void CCamera::ZoomIn()
{
	m_ProjectionScale -= DT;
	
	if (0.5f > m_ProjectionScale)
	{
		m_ProjectionScale = 0.5f;
		m_ZoomIn = false;
	}
}

void CCamera::ZoomOut()
{
	m_ProjectionScale += DT * 2.f;

	if (1.f < m_ProjectionScale)
	{
		m_ProjectionScale = 1.f;
		m_ZoomOut = false;
	}
}

void CCamera::Render()
{
	SortGameObject();

	g_Trans.matView = m_matView;
	g_Trans.matProj = m_matProj;

	// Opaque
	for (size_t i = 0; i < m_vecOpaque.size(); ++i)
	{
		m_vecOpaque[i]->Render();
	}

	// Masked
	for (size_t i = 0; i < m_vecMasked.size(); ++i)
	{
		m_vecMasked[i]->Render();
	}

	// Transparent
	for (size_t i = 0; i < m_vecTransparent.size(); ++i)
	{
		m_vecTransparent[i]->Render();
	}

	// Particles
	for (size_t i = 0; i < m_vecParticles.size(); ++i)
	{
		m_vecParticles[i]->Render();
	}

	for (size_t i = 0; i < m_vecPostProcess.size(); ++i)
	{
		CRenderMgr::GetInst()->PostProcessCopy();
		m_vecPostProcess[i]->Render();
	}

	for (size_t i = 0; i < m_vecUI.size(); ++i)
	{
		m_vecUI[i]->Render();
	}

	// Runtime �� Domain Type�� ���� �� �� �ֱ� ������ Render ȣ�� �ϰ� clear ������
	m_vecOpaque.clear();
	m_vecMasked.clear();
	m_vecTransparent.clear();
	m_vecParticles.clear();
	m_vecPostProcess.clear();
	m_vecUI.clear();
}

void CCamera::ShakingIn()
{
	m_ProjectionScale -= DT * 30.f;

	if (0.85f > m_ProjectionScale)
	{
		m_ProjectionScale = 0.85f;
		m_ShakingIn = false;
	}
}

void CCamera::ShakingOut()
{
	m_ProjectionScale += DT * 30.f;

	if (1.f < m_ProjectionScale)
	{
		m_ProjectionScale = 1.f;
		m_ShakingOut = false;
	}
}

void CCamera::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Priority, sizeof(int), 1, _pFile);
	fwrite(&m_LayerCheck, sizeof(UINT), 1, _pFile);
	fwrite(&m_ProjType, sizeof(PROJ_TYPE), 1, _pFile);
	fwrite(&m_Width, sizeof(float), 1, _pFile);
	fwrite(&m_Height, sizeof(float), 1, _pFile);
	fwrite(&m_Far, sizeof(float), 1, _pFile);
	fwrite(&m_AspectRatio, sizeof(float), 1, _pFile);
	fwrite(&m_FOV, sizeof(float), 1, _pFile);
	fwrite(&m_ProjectionScale, sizeof(float), 1, _pFile);
}

void CCamera::LoadFromFile(FILE* _pFile)
{
	fread(&m_Priority, sizeof(int), 1, _pFile);
	fread(&m_LayerCheck, sizeof(UINT), 1, _pFile);
	fread(&m_ProjType, sizeof(PROJ_TYPE), 1, _pFile);
	fread(&m_Width, sizeof(float), 1, _pFile);
	fread(&m_Height, sizeof(float), 1, _pFile);
	fread(&m_Far, sizeof(float), 1, _pFile);
	fread(&m_AspectRatio, sizeof(float), 1, _pFile);
	fread(&m_FOV, sizeof(float), 1, _pFile);
	fread(&m_ProjectionScale, sizeof(float), 1, _pFile);
}