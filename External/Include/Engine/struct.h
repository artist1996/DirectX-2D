#pragma once

struct Vtx
{
	Vec3	vPos;
	Vec4	vColor;
	Vec2	vUV;
};

// ====================
// 상수 버퍼 연동 구조체
// ====================
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;

	Matrix matWV;
	Matrix matWVP;
};

extern tTransform g_Trans;

struct tMtrlConst
{
	int		iArr[4];
	float	fArr[4];
	Vec2	v2Arr[4];
	Vec4	v4Arr[4];
	Matrix  matArr[4];
	int		btex[TEX_PARAM::END + 2];
};

struct tSpriteInfo
{
	Vec2 vLeftTopUV;
	Vec2 vSliceUV;
	Vec2 vBackGroundUV;
	Vec2 vOffsetUV;
	int  UseFlipBook;
	int  Padding[3];
};

struct tPixel
{
	BYTE b;
	BYTE g;
	BYTE r;
	BYTE a;
};

struct tDebugShapeInfo
{
	DEBUG_SHAPE Shape;
	Vec3		vPos;
	Vec3		vScale;
	Vec3		vRot;
	Matrix		matWorld;
	Vec4		vColor;

	float		LifeTime;
	float		Age;

	bool		DepthTest;
};

struct tTask
{
	TASK_TYPE Type;
	DWORD_PTR Param_0;
	DWORD_PTR Param_1;
};

struct tLight
{
	Vec4 Color;		// 빛의 색상
	Vec4 Ambient;	// 환경광
};

struct tLightInfo
{
	tLight		Info;	  // 광원 색상 정보
	Vec3		WorldPos; // 광원 위치
	Vec3		WorldDir; // 광원이 진행하는 방향
	
	float		Radius;	  // 광원의 반경
	float		Angle;    // 광원 범위 각도

	LIGHT_TYPE	Type;	  // 광원 종류

	int			Padding[3];	 // 패딩
};

struct tParticle
{
	Vec3  vLocalPos;
	Vec3  vWorldPos;
	Vec3  vScale;
	Vec4  vColor;
	
	Vec3  vForce;
	Vec3  vVelocity;

	float Mass;
	int   Active;

	int   Padding[3];
};

struct tGlobalData
{
	float   g_DT;            // DT
	float   g_EngineDT;      // Engine DT
	float   g_Time;          // Time
	float   g_EngineTime;    // Engine Time

	Vec2    g_Resolution;    // RenderTarget 해상도 정보

	int     g_Light2DCount;  // 2D 광원 개수
	int     g_Light3DCount;  // 3D 광원 개수
};

extern tGlobalData g_GlobalData;