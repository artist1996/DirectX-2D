#include "pch.h"
#include "CEditorCameraScript.h"

CEditorCameraScript::CEditorCameraScript()
	: CScript(-1)
	, m_Speed(500.f)
{
}

CEditorCameraScript::~CEditorCameraScript()
{
}

void CEditorCameraScript::Tick()
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
		if (PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
		{
			Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
		}

		else
		{
			Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		}
	}
}

void CEditorCameraScript::OrthoGraphicMove()
{
	float Speed = m_Speed;

	if (KEY_PRESSED(KEY::LSHIFT))
		Speed *= 3.f;

	Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += EngineDT * Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= EngineDT * Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= EngineDT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += EngineDT * Speed;
	}

	float ProjScale = Camera()->GetProjScale();

	if (KEY_PRESSED(KEY::_8))
		ProjScale += EngineDT;
		
	if (KEY_PRESSED(KEY::_9))
		ProjScale -= EngineDT;

	Transform()->SetRelativePos(vPos);
	Camera()->SetProjScale(ProjScale);
}

void CEditorCameraScript::PerspectiveMove()
{
	float Speed = m_Speed;

	if (KEY_PRESSED(KEY::LSHIFT))
		Speed *= 3.f;

	Vec3 vFront = Transform()->GetWorldDir(DIR::FRONT);
	Vec3 vRight = Transform()->GetWorldDir(DIR::RIGHT);

	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos += vFront * Speed * EngineDT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos -= vFront * Speed * EngineDT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos -= vRight * EngineDT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos += vRight * EngineDT * Speed;
	}

	Transform()->SetRelativePos(vPos);

	if (KEY_PRESSED(KEY::LBTN))
	{
		CKeyMgr::GetInst()->MouseCaptrue(true);

		// vDir.x ==> y축 회전
		// vDir.y ==> x축 회전
		Vec2 vDir = CKeyMgr::GetInst()->GetDragDir();

		Vec3 vRot = Transform()->GetRelativeRotation();

		vRot.y += vDir.x * XM_PI * EngineDT;
		vRot.x += vDir.y * XM_PI * EngineDT;
		Transform()->SetRelativeRotation(vRot);
	}

	else if (KEY_RELEASED(KEY::LBTN))
	{
		CKeyMgr::GetInst()->MouseCaptrue(false);
	}
}