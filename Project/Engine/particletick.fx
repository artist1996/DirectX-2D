#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"
#include "struct.fx"


RWStructuredBuffer<tParticle>   ParticleBuffer   : register(u0);
RWStructuredBuffer<tSpawnCount> SpawnCountBuffer : register(u1);
Texture2D                       NoiseTex         : register(t20);

#define ParticleObjectPos   g_vec4_0.xyz
#define MAX_COUNT           g_int_0
#define PARTICLE            ParticleBuffer[_ID.x]

[numthreads(1024, 1, 1)]
void CS_ParticleTick(int3 _ID : SV_DispatchThreadID)
{
    if (MAX_COUNT <= _ID.x)
        return;
    
    if (false == PARTICLE.Active)
    {
        int SpawnCount = SpawnCountBuffer[0].iSpawnCount;
        
        while (0 < SpawnCount)
        {
            int Origin = 0;
               
            InterlockedCompareExchange(SpawnCountBuffer[0].iSpawnCount
                                     , SpawnCount
                                     , SpawnCountBuffer[0].iSpawnCount - 1
                                     , Origin);
            
            if(SpawnCount == Origin)
            {
                float2 vUV = (float2) 0.f;
                
                // Thread �� UV �� ���� �ϱ� ���� ID ���� �̿� �� 0 ~ 1 ������ ����ȭ
                vUV.x = ((float) _ID.x / (float) (MAX_COUNT - 1)) + g_EngineTime * 0.5f;
                
                // sin �׷����� �������ش�.
                vUV.y = sin(vUV.x * 20 * PI) * 0.5f + g_EngineTime * 0.1f;
                
                float3 vNoise = NoiseTex.SampleLevel(g_sam_0, vUV, 0).xyz;
                
                float  BoxScale = 3000.f;
                float3 vRandomPos = (float3)0.f;
                
                // Random �� Local Position �� ����ش�.
                vRandomPos.x = vNoise.x * BoxScale - BoxScale / 2.f;
                vRandomPos.y = vNoise.y * BoxScale - BoxScale / 2.f;
                vRandomPos.z = vNoise.z * BoxScale - BoxScale / 2.f;
                
               
                
                // Particle �� Local Position �� RandomPosition �� �־��ְ�,
                // �ش� LocalPos�� Particle�� RelatviePos �� �����ش�.
                PARTICLE.vLocalPos = vRandomPos;
                PARTICLE.vLocalPos.y = 624.f;
                PARTICLE.vLocalPos.z = 0.f;
                PARTICLE.vWorldPos = PARTICLE.vLocalPos + ParticleObjectPos;
                //PARTICLE.vWorldPos.x = cos(angle) * radius + ParticleObjectPos;
                //PARTICLE.vWorldPos.y = sin(angle) * radius + ParticleObjectPos;
                
                PARTICLE.Age = 0.f;
                PARTICLE.NormalizedAge = 0.f;
                PARTICLE.Life = 20.f;
                PARTICLE.Active = true;
                break;
            }
            
            SpawnCount = SpawnCountBuffer[0].iSpawnCount;
        }      
    }
    else
    {   
        float rotationSpeed = 2.f;
        float radius = 1.f;
        float angle = PARTICLE.vLocalPos.x * rotationSpeed + g_EngineTime;
        
        PARTICLE.vWorldPos += PARTICLE.vVelocity * g_EngineDT;
        PARTICLE.Age += g_EngineDT;
        
        if (PARTICLE.Life <= PARTICLE.Age)
        {
            PARTICLE.Active = false;
        }
    }

    //ParticleBuffer[_ID.x].vWorldPos.y += g_EngineDT * 100.f;
}



#endif