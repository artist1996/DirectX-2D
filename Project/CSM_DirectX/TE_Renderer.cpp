#include "pch.h"
#include "TE_Renderer.h"

TE_Renderer::TE_Renderer()
	: m_TileSize(0.f,0.f)
	, m_TileIdx(0)
	, m_UseGrid(false)

{
}

TE_Renderer::~TE_Renderer()
{
}

void TE_Renderer::Init()
{
}

void TE_Renderer::Update()
{
	if (!IsActive())
		return;
}
