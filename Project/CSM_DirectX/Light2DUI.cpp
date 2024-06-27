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

	tLight		Info;		 // ���� ���� ����
	Vec3		WorldPos;	 // ���� ��ġ
	Vec3		WorldDir;	 // ������ �����ϴ� ����
							 
	float		Radius;		 // ������ �ݰ�
	float		Angle;		 // ���� ���� ����
							 
	LIGHT_TYPE	Type;		 // ���� ����

	int			Padding[3];	 // �е�
}