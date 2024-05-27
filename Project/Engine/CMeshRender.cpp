#include "pch.h"
#include "CMeshRender.h"
#include "CAssetMgr.h"
#include "CTransform.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::FinalTick()
{
}

void CMeshRender::Render()
{
	if (!GetMesh() || !GetMaterial() || !GetMaterial()->GetShader())
		return;

	Transform()->Binding();
	GetMaterial()->Binding();
	GetMesh()->Render();
}