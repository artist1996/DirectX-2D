#include "pch.h"
#include "CLight2D.h"

#include "CRenderMgr.h"
#include "CTransform.h"

CLight2D::CLight2D()
	: CComponent(COMPONENT_TYPE::LIGHT2D)
	, m_Info{}
{
}

CLight2D::~CLight2D()
{
}

void CLight2D::FinalTick()
{
	m_Info.WorldPos = Transform()->GetRelativePos();
	m_Info.WorldDir = Transform()->GetRelativeDir(DIR::RIGHT);

	// RenderMgr ¿¡ µî·Ï
	CRenderMgr::GetInst()->RegisterLight2D(this);
}