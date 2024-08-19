#include "pch.h"
#include "ParticleSystemUI.h"

#include <Engine/CGameObject.h>
#include <Engine/CParticleSystem.h>

ParticleSystemUI::ParticleSystemUI()
	: ComponentUI(COMPONENT_TYPE::PARTICLESYSTEM)
{
}

ParticleSystemUI::~ParticleSystemUI()
{
}

void ParticleSystemUI::Update()
{
	Title();

	CParticleSystem* pParticleSys = GetTargetObject()->ParticleSystem();

	Ptr<CTexture> ParticleTex = pParticleSys->GetParticleTex();
	int MaxParticleCount = pParticleSys->GetMaxParticleCount();
	tParticleModule& Module = pParticleSys->GetModuleInfo();

	// Texture Image
	ImVec2 uv_min = ImVec2(0.0f, 0.0f);
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);

	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

	ImGui::Image(ParticleTex->GetSRV().Get(), ImVec2(100.f, 100.f), uv_min, uv_max, tint_col, border_col);

	// Spawn
	ImGui::Text("Spawn Rate");
	ImGui::SameLine(150);
	ImGui::DragInt("##SpawnRate", (int*)&Module.SpawnRate);

	ImGui::Text("Spawn Color");
	ImGui::SameLine(150);
	ImGui::DragFloat4("##SpawnColor", Module.vSpawnColor, 0.01f);

	ImGui::Text("Min Scale");
	ImGui::SameLine(150);
	ImGui::DragFloat4("##SpawnMinScale", Module.vSpawnMinScale);

	ImGui::Text("Max Scale");
	ImGui::SameLine(150);
	ImGui::DragFloat4("##SpawnMaxScale", Module.vSpawnMaxScale);

	ImGui::Text("Min Life");
	ImGui::SameLine(150);
	ImGui::DragFloat("##SpawnMinLife", &Module.MinLife);

	ImGui::Text("Max Life");
	ImGui::SameLine(150);
	ImGui::DragFloat("##SpawnMaxLife", &Module.MaxLife);
	
	ImGui::Text("Spawn Shape");
	ImGui::SameLine(150);
	ImGui::DragInt("##SpawnShape", (int*)&Module.SpawnShape);
	
	ImGui::Text("Spawn Shape Scale");
	ImGui::SameLine(150);
	ImGui::DragFloat3("##SpawnShapeScale", Module.SpawnShapeScale);

	Module.BlockSpawnShape;		// 0 : Box, 1 : Sphere
	Module.BlockSpawnShapeScale; // SpawnShapeScale.x == Radius

	Module.SpaceType;			// 0 : Local Space, 1 : World Space

	// Spawn Burst
	Module.SpawnBurstCount;		// 한번에 발생시키는 Particle 수
	Module.SpawnBurstRepeat;		// 반복 여부
	Module.SpawnBurstRepeatTime; // 반복 생성 시간

	// Add Velocity
	Module.AddVelocityType;		// 0 : Random, 1 : FromCenter, 2 : ToCenter, 3 : Fixed
	Module.AddVelocityFixedDir;
	Module.AddMinSpeed;			// 최소 속력
	Module.AddMaxSpeed;			// 최대 속력

	// Scale Module
	Module.StartScale;
	Module.EndScale;

	// Drag Module
	Module.DestNormalizedAge;
	Module.LimitSpeed;

	// Noise Force Module
	Module.NoiseForceTerm;		// Noise Force 적용시키는 텀
	Module.NoiseForceScale;		// Noise Force 크기

	// Render Module
	Module.EndColor;				// 최종 색상
	Module.FadeOut;				// 0 : Off, 1 : Normalized Age
	Module.FadeOutStartRatio;	// FadeOut 효과가 시작되는 Normalized Age 지점
	Module.VelocityAlignment;	// 속도 정렬 0 : Off, 1 : On

	// Moudle On / Off
	Module.Module[(UINT)PARTICLE_MODULE::END];

	SetChildSize(ImVec2(500.f, 2000.f));
}