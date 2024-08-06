#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"
#include "struct.fx"


RWStructuredBuffer<tParticle> ParticleBuffer : register(u0);

#define MAX_COUNT       g_int_0
#define PARTICLE        ParticleBuffer[_ID.x]

[numthreads(1024, 1, 1)]
void CS_ParticleTick(int3 _ID : SV_DispatchThreadID)
{
    if (MAX_COUNT <= _ID.x)
        return;
    
    if (!PARTICLE.Active)
        return;
    
    PARTICLE.vWorldPos += PARTICLE.vVelocity * g_EngineDT;
    
    //ParticleBuffer[_ID.x].vWorldPos.y += g_EngineDT * 100.f;
}



#endif