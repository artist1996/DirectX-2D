#include "pch.h"
#include "CParticleSystem.h"

#include "CDevice.h"
#include "CAssetMgr.h"
#include "CStructuredBuffer.h"

#include "CTransform.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_TickCS(nullptr)
	, m_MaxParticleCount(100)
{
	// Mesh Material
	
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"ParticleRenderMtrl"));

	// ParticleTick ComputeShader
	m_TickCS = (CParticleTickCS*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"ParticleTickCS").Get();

	// Particle 100°³ Init
	tParticle arrParticle[100] = {};

	Vec2 vResolution = CDevice::GetInst()->GetResolution();
	Vec3 vStart = Vec3(-vResolution.x / 2.f, 0.f, 100.f);
	float Step = vResolution.x / (float)m_MaxParticleCount;

	for (int i = 0; i < m_MaxParticleCount; ++i)
	{
		arrParticle[i].Active = true;
		arrParticle[i].Mass = 1.f;
		arrParticle[i].vLocalPos = Vec3(0.f, 0.f, 0.f);
		arrParticle[i].vWorldPos = vStart + Vec3(Step * (float)i, 0.f, 0.f);
	}

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticleCount, SB_TYPE::SRV_UAV, true, arrParticle);
}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;
}

void CParticleSystem::FinalTick()
{
	m_TickCS->SetParticleBuffer(m_ParticleBuffer);
	m_TickCS->Execute();
}

void CParticleSystem::Render()
{
	Transform()->Binding();

	m_ParticleBuffer->Binding(20);

	GetMaterial()->Binding();

	GetMesh()->Render_Particle(m_MaxParticleCount);
}

void CParticleSystem::SaveToFile(FILE* _File)
{
}

void CParticleSystem::LoadFromFile(FILE* _File)
{
}
