#pragma once

struct Vtx
{
	Vec3	vPos;
	Vec4	vColor;
	Vec2	vUV;
};

// ====================
// ��� ���� ���� ����ü
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
	Vec4 Color;		// ���� ����
	Vec4 Ambient;	// ȯ�汤
};

struct tLightInfo
{
	tLight		Info;	  // ���� ���� ����
	Vec3		WorldPos; // ���� ��ġ
	Vec3		WorldDir; // ������ �����ϴ� ����
	
	float		Radius;	  // ������ �ݰ�
	float		Angle;    // ���� ���� ����

	LIGHT_TYPE	Type;	  // ���� ����

	int			Padding[3];	 // �е�
};

struct tParticle
{
	Vec4   vColor;
	Vec3   vLocalPos;
	Vec3   vWorldPos;
	Vec3   vWorldInitScale;
	Vec3   vWorldIdCurrentScale;
	Vec3   vWorldRotation;

	Vec3   vForce;				// Particle�� ������ ��
	Vec3   vVelocity;

	float  NoiseForceAccTime;	// Noise Force �ҿ� �����ϴ� ���� �ð�
	Vec3   NoiseForceDir;		// Noise Force �� ����

	float  Mass;
	float  Life;
	float  Age;
	float  NormalizedAge;
	int    Active;

	Vec2   Padding;
};

// Particle Module
struct tParticleModule
{
	// Spawn
	UINT  SpawnRate;			// �ʴ� ��ƼŬ �������� (Spawn Per Second)
	Vec4  vSpawnColor;			// ���� ���� ����
	Vec4  vSpawnMinScale;		// ���� �� �ּ� ũ��
	Vec4  vSpawnMaxScale;		// ���� �� �ִ� ũ��
	
	float MinLife;				// �ּ� ����
	float MaxLife;				// �ִ� ����

	UINT  SpawnShape;			// 0 : Box, 1 : Sphere
	Vec3  SpawnShapeScale;		// SpawnShapeScale.x == Radius
		  
	UINT  BlockSpawnShape;		// 0 : Box, 1 : Sphere
	Vec3  BlockSpawnShapeScale; // SpawnShapeScale.x == Radius
		  
	UINT  SpaceType;			// 0 : Local Space, 1 : World Space

	// Spawn Burst
	UINT  SpawnBurstCount;		// �ѹ��� �߻���Ű�� Particle ��
	UINT  SpawnBurstRepeat;		// �ݺ� ����
	float SpawnBurstRepeatTime; // �ݺ� ���� �ð�

	// Add Velocity
	UINT  AddVelocityType;		// 0 : Random, 1 : FromCenter, 2 : ToCenter, 3 : Fixed
	Vec3  AddVelocityFixedDir;
	float AddMinSpeed;			// �ּ� �ӷ�
	float AddMaxSpeed;			// �ִ� �ӷ�

	// Scale Module
	float StartScale;
	float EndScale;
	
	// Drag Module
	float DestNormalizedAge;
	float LimitSpeed;

	// Noise Force Module
	float NoiseForceTerm;		// Noise Force �����Ű�� ��
	float NoiseForceScale;		// Noise Force ũ��

	// Render Module
	Vec3  EndColor;				// ���� ����
	UINT  FadeOut;				// 0 : Off, 1 : Normalized Age
	float FadeOutStartRatio;	// FadeOut ȿ���� ���۵Ǵ� Normalized Age ����
	UINT  VelocityAlignment;	// �ӵ� ���� 0 : Off, 1 : On

	// Moudle On / Off
	int Module[(UINT)PARTICLE_MODULE::END];
};

struct tGlobalData
{
	float   g_DT;            // DT
	float   g_EngineDT;      // Engine DT
	float   g_Time;          // Time
	float   g_EngineTime;    // Engine Time

	Vec2    g_Resolution;    // RenderTarget �ػ� ����

	int     g_Light2DCount;  // 2D ���� ����
	int     g_Light3DCount;  // 3D ���� ����
};

extern tGlobalData g_GlobalData;