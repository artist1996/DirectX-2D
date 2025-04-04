#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_IndependentScale(false)
{
}

CTransform::~CTransform()
{
}

void CTransform::FinalTick()
{
	// 오브젝트의 월드 행렬 계산
	// 크기 행렬
	Matrix matScale = XMMatrixScaling(m_RelativeScale.x, m_RelativeScale.y, m_RelativeScale.z);
	
	// 이동 행렬
	Matrix matTranslation = XMMatrixTranslation(m_RelativePos.x, m_RelativePos.y, m_RelativePos.z);

	// 회전 행렬
	Matrix matRot = XMMatrixRotationX(m_RelativeRotation.x)
				  * XMMatrixRotationY(m_RelativeRotation.y)
				  * XMMatrixRotationZ(m_RelativeRotation.z);

	m_matWorld = matScale * matRot * matTranslation;

	static Vec3 vDefaultAxis[3] = 	
	{
		Vec3(1.f, 0.f, 0.f),
		Vec3(0.f, 1.f, 0.f),
		Vec3(0.f, 0.f, 1.f),
	};

	// HLSL mul
	// w를 1로 확장
	
	for (int i = 0; i < 3; ++i)
	{
		m_RelativeDir[i] = XMVector3TransformNormal(vDefaultAxis[i], matRot);
		m_RelativeDir[i].Normalize();
	}

	// 부모 오브젝트가 있는지 확인
	if (GetOwner()->GetParent())
	{
		// 부모의 월드행렬을 곱해서 최종 월드행렬을 계산함
		const Matrix& matParentWorldMat = GetOwner()->GetParent()->Transform()->GetWorldMatrix();
		
		if (m_IndependentScale)
		{ 
			// 부모의 크기 행렬의 역행렬을 구해서 부모의 크기에 상대적인 크기를 갖지 않고 독립적인 크기를 갖게 해준다.
			Vec3 vParentScale = GetOwner()->GetParent()->Transform()->GetRelativeScale();
			Matrix matParentScale = XMMatrixScaling(vParentScale.x, vParentScale.y, vParentScale.z);
			Matrix matParentScaleInv = XMMatrixInverse(nullptr, matParentScale);

			m_matWorld = m_matWorld * matParentScaleInv * matParentWorldMat;
			//m_matWorld = m_matWorld * matParentWorldMat * matParentScaleInv;
		}

		else
		{
			m_matWorld *= matParentWorldMat;
		}
		// 최종 월드기준 오브젝트의 방향벡터를 구함
		for (int i = 0; i < 3; ++i)
		{
			m_WorldDir[i] = XMVector3TransformNormal(vDefaultAxis[i], m_matWorld);
			m_WorldDir[i].Normalize();

			if (L"Player" == GetOwner()->GetName())
				int a = 0;
		}
	}

	// 부모가 없으면 RelativeDir 이 곧 World Dir
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			m_WorldDir[i] = m_RelativeDir[i];
		}
	}
}

Vec3 CTransform::GetWorldScale()
{
	Vec3 vWorldScale = Vec3(1.f, 1.f, 1.f);

	CGameObject* pObject = GetOwner();

	while (pObject)
	{
		vWorldScale *= pObject->Transform()->GetRelativeScale();

		// 만약 독립적인 크기를 가진 Object 라면 break 해줘야한다.
		if (pObject->Transform()->m_IndependentScale)
			break;

		pObject = GetOwner()->GetParent();
	}

	return vWorldScale;
}

void CTransform::Binding()
{
	g_Trans.matWorld = m_matWorld;
	g_Trans.matWV = g_Trans.matWorld * g_Trans.matView;
	g_Trans.matWVP = g_Trans.matWV * g_Trans.matProj;

	CConstBuffer* pTransformCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformCB->SetData(&g_Trans);
	pTransformCB->Binding();
}

void CTransform::SaveToFile(FILE* _pFile)
{	
	fwrite(&m_RelativePos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_RelativeScale, sizeof(Vec3), 1, _pFile);
	fwrite(&m_RelativeRotation, sizeof(Vec3), 1, _pFile);
	fwrite(&m_IndependentScale, sizeof(bool), 1, _pFile);
}

void CTransform::LoadFromFile(FILE* _pFile)
{
	fread(&m_RelativePos, sizeof(Vec3), 1, _pFile);
	fread(&m_RelativeScale, sizeof(Vec3), 1, _pFile);
	fread(&m_RelativeRotation, sizeof(Vec3), 1, _pFile);
	fread(&m_IndependentScale, sizeof(bool), 1, _pFile);
}