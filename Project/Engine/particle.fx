#ifndef _PARTICLE
#define _PARTICLE

#include "value.fx"
#include "struct.fx"

StructuredBuffer<tParticle> ParticleBuffer : register(t20);

struct VS_IN
{
    float3 vPos   : POSITION;
    float2 vUV    : TEXCOORD;
    
    uint   InstID : SV_InstanceID;
};

struct VS_OUT
{
    float3 vLocalPos : POSITION; 
    
    uint   InstID    : FOG;
};

VS_OUT VS_Particle(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vLocalPos = _in.vPos;
    output.InstID    = _in.InstID;
    
    return output;
}

struct GS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV       : TEX_COORD;
    uint   InstID    : FOG;
};

[maxvertexcount(6)]
void GS_Particle(point VS_OUT _in[1], inout TriangleStream<GS_OUT> _OutStream)
{
    GS_OUT output[4] = { (GS_OUT) 0.f, (GS_OUT) 0.f, (GS_OUT) 0.f, (GS_OUT) 0.f };
    
    // 0 -- 1
    // | \  |
    // 3 -- 2
    
    if(false == ParticleBuffer[_in[0].InstID].Active)
        return;
    
    float3 fScale = ParticleBuffer[_in[0].InstID].vWorldScale;
    float3 vViewPos = mul(float4(ParticleBuffer[_in[0].InstID].vWorldPos, 1.f), matView);
    
    // RectMesh 정점 세팅
    output[0].vPosition.xyz = vViewPos + float3(-fScale.x / 2.f,  fScale.y / 2.f, 0.f);
    output[1].vPosition.xyz = vViewPos + float3( fScale.x / 2.f,  fScale.y / 2.f, 0.f);
    output[2].vPosition.xyz = vViewPos + float3( fScale.x / 2.f, -fScale.y / 2.f, 0.f);
    output[3].vPosition.xyz = vViewPos + float3(-fScale.x / 2.f, -fScale.y / 2.f, 0.f);
    
    for (int i = 0; i < 4; ++i)
    {
        output[i].vPosition.w = 1.f;
        output[i].vPosition   = mul(output[i].vPosition, matProj);
        output[i].InstID      = _in[0].InstID;
    }
    
    output[0].vUV = float2(0.f, 0.f);
    output[1].vUV = float2(1.f, 0.f);
    output[2].vUV = float2(1.f, 1.f);
    output[3].vUV = float2(0.f, 1.f);

    // Stream 출력
    _OutStream.Append(output[0]);
    _OutStream.Append(output[2]);
    _OutStream.Append(output[3]);
    
    _OutStream.RestartStrip();
  
    _OutStream.Append(output[0]);
    _OutStream.Append(output[1]);
    _OutStream.Append(output[2]);

}
// 1. 비활성화 파티클 처리
// GeometryShader 에서 정점을 생성 및 삭제
// 비활성화된 파티클을 렌더링할 차례면, 출력스트림을 비워서, 중간에 파이프라인을 종료시킨다.

// 2. 파티클 빌보드 처리

float4 PS_Particle(GS_OUT _in) : SV_Target
{
    float4 vColor = float4(1.f, 0.f, 0.f, 1.f);
    
    if(g_btex_0)
    {
        vColor  = g_tex_0.Sample(g_sam_0, _in.vUV);
        vColor *= ParticleBuffer[_in.InstID].vColor;
    }
    
    return vColor;
}

#endif