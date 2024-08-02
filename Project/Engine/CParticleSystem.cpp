#include "pch.h"
#include "CParticleSystem.h"

#include "CStructuredBuffer.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_MaxParticleCount(100)
{
	//m_ParticleBuffer = new CStructuredBuffer;
	//m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticleCount, SB_TYPE::SRV_UAV, true);
}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;
}

void CParticleSystem::FinalTick()
{
}

void CParticleSystem::Render()
{
}

void CParticleSystem::SaveToFile(FILE* _File)
{
}

void CParticleSystem::LoadFromFile(FILE* _File)
{
}
