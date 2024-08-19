#ifndef _FUNC
#define _FUNC

#include "struct.fx"
#include "value.fx"

int IsBinding(Texture2D _tex)
{
    int width = 0; int height = 0;
    _tex.GetDimensions(width, height);
    
    if(0 == width || 0 == height)
        return false;
    
    return true;
}

void CalculateLight2D(int _LightIdx, float3 _WorldPos , inout tLight _Light)
{
    tLightInfo Info = g_Light2DBuffer[_LightIdx];
        
    if (0 == Info.Type)
    {
        _Light.Color.rgb += Info.Info.Color.rgb;
        _Light.Ambient.rgb += Info.Info.Ambient.rgb;
    }
    // Point Light
    else if (1 == Info.Type)
    {
        float fDist = distance(Info.WorldPos.xy, _WorldPos.xy);     // �� �Ÿ��� ���� ��Į�� ������ ��ȯ�����ִ� �Լ�
        //float Pow = saturate(1.f - (fDist / g_Light2DBuffer[0].Radius));
        float fPow = saturate(cos(saturate(fDist / Info.Radius) * (PI / 2.f)));
        
        _Light.Color.rgb += Info.Info.Color.rgb * fPow;
        _Light.Ambient.rgb += Info.Info.Ambient.rgb;
    }
    // Spot Light
    else
    {     
        float2 PixelDir = _WorldPos.xy - Info.WorldPos.xy;         // �ȼ��� ���������� ������ �������� ���� ����
        float fDist = length(PixelDir);                            // Radius �� ���� ������ Pixel �� Dist ��
        float2 Normalize = normalize(PixelDir);                    // ����ȭ ���ͷ� ����� �� ��
        float Dot = saturate(dot(Info.WorldDir.xy, Normalize.xy)); // �� ���� ������ ���� ���� cos ��Ÿ���� ������ش�.
              
        if (Dot > cos(Info.Angle) && fDist < Info.Radius)
        {
            _Light.Color.rgb += Info.Info.Color.rgb;
        }
    }    
}

float3 GetRandom(in Texture2D _NoiseTexture, uint _ID, uint _maxID)
{
    float2 vUV = (float2) 0.f;
    vUV.x = ((float) _ID / (float) (_maxID - 1) + g_EngineTime * 0.5f);
    vUV.y = sin(vUV.x * 20 * PI) * 0.5f + g_EngineTime * 0.1f;
    
    float3 vRandom = _NoiseTexture.SampleLevel(g_sam_1, vUV, 0).xyz;
    
    return vRandom;
}

#endif