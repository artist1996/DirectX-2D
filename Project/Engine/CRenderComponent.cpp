#include "pch.h"
#include "CRenderComponent.h"

CRenderComponent::CRenderComponent(COMPONENT_TYPE _Type)
	: CComponent(_Type)
	, m_Mesh(nullptr)
	, m_Mtrl(nullptr)
	, m_DynamicMtrl(nullptr)
{
}

CRenderComponent::~CRenderComponent()
{
}

Ptr<CMaterial> CRenderComponent::GetSharedMaterial()
{
	m_Mtrl = m_SharedMtrl;
	return m_Mtrl;
}

void CRenderComponent::SetMaterial(Ptr<CMaterial> _Mtrl)
{
	m_Mtrl = m_SharedMtrl = _Mtrl;
}

Ptr<CMaterial> CRenderComponent::GetDynamicMaterial()
{
	if (nullptr != m_DynamicMtrl)
		return m_DynamicMtrl;

	m_Mtrl = m_DynamicMtrl = m_SharedMtrl->Clone();

	return m_Mtrl;
}