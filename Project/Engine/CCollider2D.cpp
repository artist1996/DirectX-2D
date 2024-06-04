#include "pch.h"
#include "CCollider2D.h"

#include "CTransform.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_OverlapCount(0)
	, m_IndependentScale(false)
{
}

CCollider2D::~CCollider2D()
{
}

void CCollider2D::FinalTick()
{	
	// Offset 행렬 구하기
	Matrix matTranslation = XMMatrixTranslation(m_Offset.x, m_Offset.y, m_Offset.z);
	
	// Scale 구하기
	Matrix matScale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	Matrix matObjectScaleInv = XMMatrixIdentity();

	// 독립적인 크기를 갖는다면
	if (m_IndependentScale)
	{
		// 크기 행렬의 역행렬을 곱 해준다.
		Vec3 vObjectScale = GetOwner()->Transform()->GetWorldScale();
		matObjectScaleInv = XMMatrixScaling(vObjectScale.x, vObjectScale.y, vObjectScale.z);
		matObjectScaleInv = XMMatrixInverse(nullptr, matObjectScaleInv);
	}

	m_matColWorld = matTranslation * matScale * matObjectScaleInv * GetOwner()->Transform()->GetWorldMatrix();
	
	DrawDebugRect(m_matColWorld, Vec4(0.f, 1.f, 0.f, 1.f), 0.f, false);
}

void CCollider2D::BeginOverlap(CCollider2D* _OtherCollider)
{
}

void CCollider2D::Overlap(CCollider2D* _OtherCollider)
{
}

void CCollider2D::EndOverlap(CCollider2D* _OtherCollider)
{
}