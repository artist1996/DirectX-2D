#include "pch.h"
#include "CParticleScript.h"

CParticleScript::CParticleScript()
	: CScript(SCRIPT_TYPE::PARTICLESCRIPT)
{
}

CParticleScript::~CParticleScript()
{
}

void CParticleScript::Begin()
{
	ParticleSystem()->CreateModuleBuffer();
}

void CParticleScript::Tick()
{
}