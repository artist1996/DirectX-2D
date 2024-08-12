#include "pch.h"
#include "CParticleSystem.h"

#include "CTimeMgr.h"
#include "CDevice.h"
#include "CAssetMgr.h"
#include "CStructuredBuffer.h"

#include "CTransform.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_SpawnCountBuffer(nullptr)
	, m_TickCS(nullptr)
	, m_ParticleTex(nullptr)
	, m_Time(0.f)
	, m_MaxParticleCount(1000)
{
	// Mesh Material
	
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"PointMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"ParticleRenderMtrl"));
	
	// ParticleTick ComputeShader
	m_TickCS = (CParticleTickCS*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"ParticleTickCS").Get();
	
	// Particle Texture
	m_ParticleTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\particle\\FX_Flare.png");
		
	// Particle 100°³ Init
	tParticle arrParticle[1000] = {};
	
	float Angle = XM_2PI/ m_MaxParticleCount;

	srand(time(NULL));
	
	for (int i = 0; i < m_MaxParticleCount; ++i)
	{
		arrParticle[i].Active	   = false;
		arrParticle[i].vLocalPos   = Vec3(0.f, 0.f, 0.f);
		arrParticle[i].vWorldPos   = Vec3(0.f, 0.f, 0.f);
		arrParticle[i].vWorldScale = Vec3(100.f, 100.f, 0.f);
		arrParticle[i].vColor	   = Vec4(0.8f, 0.8f, 0.5f, 0.7f);
		//arrParticle[i].vVelocity   = Vec3(cosf(Angle * (float)i), sinf(Angle * (float)i), 0.f) * 5.f;
		arrParticle[i].vVelocity = Vec3(cosf(rand() % 360), -1.f, 0.f) * 200.f;
	}
	
	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticleCount, SB_TYPE::SRV_UAV, true, nullptr);
	m_ParticleBuffer->SetData(&arrParticle);
	
	m_SpawnCountBuffer = new CStructuredBuffer;
	m_SpawnCountBuffer->Create(sizeof(tSpawnCount), 1, SB_TYPE::SRV_UAV, true, nullptr);
}

CParticleSystem::~CParticleSystem()
{
	SAFE_DELETE(m_ParticleBuffer);
	SAFE_DELETE(m_SpawnCountBuffer);
}

void CParticleSystem::FinalTick()
{
	// Spawn Count
	m_Time += EngineDT;

	if (0.05f <= m_Time)
	{
		tSpawnCount count = {};
		count.iSpawnCount = 1;
		m_SpawnCountBuffer->SetData(&count);
	
		m_Time = 0.f;
	}

	m_TickCS->SetParticleWorldPos(Transform()->GetWorldPos());
	m_TickCS->SetParticleBuffer(m_ParticleBuffer);
	m_TickCS->SetSpawnCountBuffer(m_SpawnCountBuffer);
	m_TickCS->Execute();
}

void CParticleSystem::Render()
{
	// Transform Binding
	Transform()->Binding();

	// Particle Buffer Binding
	m_ParticleBuffer->Binding(20);

	// Material Binding
	GetMaterial()->SetTexParam(TEX_0, m_ParticleTex);
	GetMaterial()->Binding();

	// Rendering
	GetMesh()->Render_Particle(m_MaxParticleCount);

	m_ParticleBuffer->Clear(20);
}

void CParticleSystem::SaveToFile(FILE* _File)
{
}

void CParticleSystem::LoadFromFile(FILE* _File)
{
}
