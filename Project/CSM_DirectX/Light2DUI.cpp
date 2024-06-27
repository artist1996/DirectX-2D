#include "pch.h"
#include "Light2DUI.h"
#include <Engine/CLight2D.h>

Light2DUI::Light2DUI()
	: ComponentUI(COMPONENT_TYPE::LIGHT2D)
{
}

Light2DUI::~Light2DUI()
{
}

void Light2DUI::Update()
{
	Title();

	tLight		Info;		 // 광원 색상 정보
	Vec3		WorldPos;	 // 광원 위치
	Vec3		WorldDir;	 // 광원이 진행하는 방향
							 
	float		Radius;		 // 광원의 반경
	float		Angle;		 // 광원 범위 각도
							 
	LIGHT_TYPE	Type;		 // 광원 종류

	int			Padding[3];	 // 패딩
}