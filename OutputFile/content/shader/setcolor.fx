#ifndef _SETCOLOR
#define _SETCOLOR

#define TEX_WIDTH  g_int_0
#define TEX_HEIGHT g_int_1

#include "value.fx"

RWTexture2D<float4> g_TargetTex : register(u0);

// SV_GroupID         : �����尡 ���� �׷��� ID �� �޴´�.
// SV_GroupThreadID   : ���� �׷쿡���� �������� ID
// SV_GroupIndex      : SV_GroupThreadID �� 1���� Index�� ��ȯ
// SV_DispathThreadID : ��ü ���� ID

// �׷�� ������ �� 
[numthreads(32, 32, 1)]
void CS_SetColor(int3 _ID : SV_DispatchThreadID)
{
    // �ȼ��� �ʰ��ؼ� �����ϴ� ������(�ʰ� ���� ������)
    if (_ID.x >= TEX_WIDTH || _ID.y >= TEX_HEIGHT)
        return;
     
    
    // �Է����� ���� _ID ���� �ȼ��� ��ǥ
    g_TargetTex[_ID.xy] = g_vec4_0;

}

#endif