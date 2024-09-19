#include "pch.h"
#include "CCameraMoveScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

CCameraMoveScript::CCameraMoveScript()
	: CScript(SCRIPT_TYPE::CAMERAMOVESCRIPT)
	, m_Target(nullptr)
	, m_CamSpeed(500.f)
	, m_BoundaryRightWidth(0.f)
	, m_BoundaryBottomHeight(0.f)
	, m_TargetMove(false)
	, m_Shaking(false)
	, m_ShakingTime(0.f)
	, m_Dir(1.f)
{
	AddScriptParam(SCRIPT_PARAM::VEC2, "Boundary LT", &m_BoundaryLT);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Boundary R Width", &m_BoundaryRightWidth);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Boundary B Height", &m_BoundaryBottomHeight);
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::Begin()
{
	m_Target = CLevelMgr::GetInst()->FindObjectByName(L"PlayerMove");
	GetOwner()->SetTarget(m_Target);
	
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	//Camera()->SetPriority(1);

	if (L"leshphon1" == pLevel->GetName())
		m_BoundaryLT = Vec2(223.f, 39.f);

	else if (L"leshphon2" == pLevel->GetName())
		m_BoundaryLT = Vec2(0.f, 40.f);

	else if (L"leshphon3" == pLevel->GetName())
		m_BoundaryLT = Vec2(0.f, 44.f);

	else if (L"leshphon4" == pLevel->GetName())
		m_BoundaryLT = Vec2(0.f, 41.f);
}

void CCameraMoveScript::Tick()
{
	m_Target = GetOwner()->GetTarget();
	//if (KEY_TAP(KEY::_1))
	//	Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	//else if(KEY_TAP(KEY::_2))
	//	Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	
	if (nullptr == m_Target)
		return;

	if (PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
	{
		// ���� ���� ī�޶� ����
		OrthoGraphicMove();
	}

	else if (PROJ_TYPE::PERSPECTIVE == Camera()->GetProjType())
	{
		// ���� ���� ī�޶� ����
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

	Vec3 vPos = m_Target->Transform()->GetWorldPos();
	if (!m_Shaking)
	{
		if (vPos.x <= m_BoundaryLT.x)
			vPos.x = m_BoundaryLT.x;

		if (vPos.y <= m_BoundaryLT.y)
			vPos.y = m_BoundaryLT.y;

		if (vPos.x >= m_BoundaryRightWidth)
			vPos.x = m_BoundaryRightWidth;

		if (vPos.y >= m_BoundaryBottomHeight)
			vPos.y = m_BoundaryBottomHeight;
	}
	else
	{
		vPos.x += m_Dir * 0.01f * DT;

		float fDist = fabs(m_StartPos.x - vPos.x) - 10.f;

		m_ShakingTime += DT;

		if (1.f > fDist)
		{
			m_Dir *= -1.f;
		}
		
		if (0.1f < m_ShakingTime)
		{
			m_Shaking = false;
			m_ShakingTime = 0.f;
		}

		if (vPos.y <= m_BoundaryLT.y)
			vPos.y = m_BoundaryLT.y;
		if (vPos.y >= m_BoundaryBottomHeight)
			vPos.y = m_BoundaryBottomHeight;
	}
	if (KEY_PRESSED(KEY::LSHIFT))
		Speed *= 3.f;

	Transform()->SetRelativePos(vPos);
}

void CCameraMoveScript::PerspectiveMove()
{
	float Speed = m_CamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
		Speed *= 3.f;
	
	Vec3 vFront = Transform()->GetWorldDir(DIR::FRONT);
	Vec3 vRight = Transform()->GetWorldDir(DIR::RIGHT);

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
	//
	//if (KEY_PRESSED(KEY::LBTN))
	//{
	//	CKeyMgr::GetInst()->MouseCaptrue(true);
	//
	//	// vDir.x ==> y�� ȸ��
	//	// vDir.y ==> x�� ȸ��
	//	Vec2 vDir = CKeyMgr::GetInst()->GetDragDir();
	//
	//	Vec3 vRot = Transform()->GetRelativeRotation();
	//	
	//	vRot.y += vDir.x * XM_PI * DT;
	//	vRot.x += vDir.y * XM_PI * DT;
	//	Transform()->SetRelativeRotation(vRot);
	//}
	//
	//else if (KEY_RELEASED(KEY::LBTN))
	//{
	//	CKeyMgr::GetInst()->MouseCaptrue(false);
	//}
}

void CCameraMoveScript::SetShaking(bool _Set)
{
	m_Shaking = _Set;
	m_StartPos = Transform()->GetRelativePos();
}

void CCameraMoveScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_CamSpeed, sizeof(float), 1, _pFile);
	fwrite(&m_BoundaryRightWidth, sizeof(float), 1, _pFile);
	fwrite(&m_BoundaryBottomHeight, sizeof(float), 1, _pFile);
}

void CCameraMoveScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_CamSpeed, sizeof(float), 1, _pFile);
	fread(&m_BoundaryRightWidth, sizeof(float), 1, _pFile);
	fread(&m_BoundaryBottomHeight, sizeof(float), 1, _pFile);
}
