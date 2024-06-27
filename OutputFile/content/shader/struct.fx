#ifndef _STRUCT
#define _STRUCT

struct tLight
{
    float4 Color;   // 빛의 색상
    float4 Ambient; // 환경광
};

struct tLightInfo
{
    tLight Info;         // 광원 색상 정보
    float3 WorldPos;     // 광원 위치
    float3 WorldDir;     // 광원이 진행하는 방향	
    float  Radius;       // 광원의 반경
    float  Angle;        // 광원 범위 각도
    uint   Type;         // 광원 종류
    int3   Padding;      // 패딩
};
#endif