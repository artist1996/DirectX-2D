#include "pch.h"
#include "CCameraMoveScript.h"

CCameraMoveScript::CCameraMoveScript()
	: m_CamSpeed(500.f)
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::Tick()
{
	if (PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
	{
		// 직교 투영 카메라 무브
		OrthoGraphicMove();
	}

	else if (PROJ_TYPE::PERSPECTIVE == Camera()->GetProjType())
	{
		// 원근 투영 카메라 무브
		PerspectiveMove();
	}

	if (KEY_TAP(KEY::P))
	{
		if(PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
		{
			Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
		}

		else
		{
			Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		}
	}
}

void CCameraMoveScript::OrthoGraphicMove()
{
	float Speed = m_CamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
		Speed *= 3.f;

	Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += DT * Speed;
	}
	
	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT * Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT * Speed;
	}

	Transform()->SetRelativePos(vPos);
}

void CCameraMoveScript::PerspectiveMove()
{
	float Speed = m_CamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
		Speed *= 3.f;
	
	Vec3 vFront = Transform()->GetDir(DIR::FRONT);
	Vec3 vRight = Transform()->GetDir(DIR::RIGHT);

	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos += vFront * Speed * DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos -= vFront * Speed * DT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos -= vRight * DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos += vRight * DT * Speed;
	}

	Transform()->SetRelativePos(vPos);

	if (KEY_PRESSED(KEY::LBTN))
	{
		CKeyMgr::GetInst()->MouseCaptrue(true);

		// vDir.x ==> y축 회전
		// vDir.y ==> x축 회전
		Vec2 vDir = CKeyMgr::GetInst()->GetDragDir();

		Vec3 vRot = Transform()->GetRelativeRotation();
		
		vRot.y += vDir.x * XM_PI * DT;
		vRot.x += vDir.y * XM_PI * DT;
		Transform()->SetRelativeRotation(vRot);
	}

	else if (KEY_RELEASED(KEY::LBTN))
	{
		CKeyMgr::GetInst()->MouseCaptrue(false);
	}
}