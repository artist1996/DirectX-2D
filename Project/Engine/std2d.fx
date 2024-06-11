#ifndef _TEST
#define _TEST

#include "value.fx"
#include "func.fx"

// Vertex Shader
struct VTX_IN
{
    float3 vPos   : POSITION;
    float4 vColor : COLOR;
    float2 vUV    : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor    : COLOR;
    float2 vUV       : TEXCOORD;
};

VTX_OUT VS_Std2D(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    // LocalSpace -> WorldSpace
    // float 3 x float4x4(matrix)
    // float3 를 float4 로 차수를 맞추어준다.
    // 동차좌표를 1로 설정, 상태행렬 4행에 들어있는 이동을 적용받겠다는 뜻
    
    float3 vWorldPos = mul(float4(_in.vPos, 1.f), matWorld);
    float4 vViewPos = mul(float4(vWorldPos, 1.f), matView);
    float4 vProjPos = mul(vViewPos, matProj);
    
    output.vPosition = vProjPos;
    output.vColor    = _in.vColor;
    output.vUV       = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VTX_OUT _in) : SV_Target
{
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
    // FlipBook 을 사용한다
    if(g_int_0)
    {
        // in.vUV : 스프라이트 를 참조할 위치를 비율로 환산한 값
        // g_vec2_0 : LeftTop UV 값
        // g_vec2_1 : Slice UV 값
        float2 vSpriteUV = g_vec2_0 + (_in.vUV * g_vec2_1);
   
        vColor = g_AtlasTex.Sample(g_sam_1, vSpriteUV);
    }
    // FlipBook 을 사용 하지 않는다.
    else
    {
        if (g_btex_0)
        {
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        
            if (g_int_1)
            {
                vColor.r *= 2.f;
            }
        }
        else
        {
            vColor = float4(1.f, 0.f, 1.f, 1.f);
        }
    } 
    //if(vColor.a == 0.f)
    //{
    //    clip(-1);
    //    discard;
    //}
    
    return vColor;
}

#endif