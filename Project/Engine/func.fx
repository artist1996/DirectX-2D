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
        _Light.Color.rgb = Info.Info.Color.rgb
                         + Info.Info.Ambient.rgb;
    }
    // Point Light
    else if (1 == Info.Type)
    {
        float fDist = distance(Info.WorldPos.xy, _WorldPos.xy);
        //float Pow = saturate(1.f - (fDist / g_Light2DBuffer[0].Radius));
        float Pow2 = saturate(cos(saturate(fDist / Info.Radius) * (PI / 2.f)));
        
        _Light.Color.rgb += Info.Info.Color.rgb * Pow2;
        _Light.Ambient.rgb += Info.Info.Ambient.rgb;
    }
    // Spot Light
    else
    {
        Info.WorldPos;
        Info.WorldDir;
        Info.Angle;
        Info.Radius;              

        float2 PixelDir = Info.WorldPos.xy - _WorldPos.xy;          // 픽셀의 월드포스와 광원의 월드포스 차이 벡터
        float fDist = length(PixelDir);                             // Radius 와 비교할 광원과 Pixel 의 Dist 값
        
        if(fDist > Info.Radius)
        {
            _Light.Color.rgb = float3(0.f, 0.f, 1.f);
            return;
        }
        
        float2 Normalize = normalize(PixelDir);                     // 정규화 벡터로 만들어 준 후
        float Dot = saturate(dot(-Info.WorldDir.xy, Normalize.xy)); // 두 방향 벡터의 내적 값인 cos 세타값을 계산해준다.
       
        if (Dot > cos(Info.Angle))
        {
            _Light.Color.rgb += Info.Info.Color.rgb;
        }
        else
        {
            _Light.Color.rgb = float3(0.f, 0.f, 1.f);
        }
    }    
}

#endif