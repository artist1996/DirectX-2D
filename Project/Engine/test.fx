#ifndef _TEST
#define _TEST


// Vertex Shader
struct VTX_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
};

VTX_OUT VS_Text(VTX_IN _in)
{
    VTX_OUT output;
    
    output.vPosition = float4(_in.vPos, 1.f);
    output.vColor = _in.vColor;
    
    return output;
}

float4 PS_Text(VTX_OUT _in) : SV_Target
{
    return float4(1.f, 0.f, 0.f, 1.f);
}

#endif