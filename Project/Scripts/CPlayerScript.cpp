#include "pch.h"
#include "CPlayerScript.h"

#include "CMissileScript.h"

CPlayerScript::CPlayerScript()
	: CScript(SCRIPT_TYPE::PLAYERSCRIPT)
	, m_Speed(500.f)
	, m_Texture(nullptr)
	, m_MissilePref(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT,"PlayerSpeed", &m_Speed);
	AddScriptParam(SCRIPT_PARAM::PREFAB, "Missile", &m_MissilePref);
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	//m_MissilePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"MissilePref");
}

void CPlayerScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_TAP(KEY::RIGHT))
	{
		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot = Vec3(0.f, 0.f, 0.f);
		Transform()->SetRelativeRotation(vRot);	
	}

	else if (KEY_PRESSED(KEY::RIGHT))
		vPos.x += m_Speed * DT;
	else if (KEY_RELEASED(KEY::RIGHT))
	{

	}

	if (KEY_TAP(KEY::LEFT))
	{
		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.x = XM_PI;
		vRot.z = XM_PI;
		Transform()->SetRelativeRotation(vRot);
		//Animator2D()->Play(1, 10, true);
	}

	else if (KEY_PRESSED(KEY::LEFT))
		vPos.x -= m_Speed * DT;
	else if (KEY_RELEASED(KEY::LEFT))
	{

	}
		//Animator2D()->Play(0, 3, true);
	
	if (KEY_TAP(KEY::UP))
	{
		//Animator2D()->Play(1, 10, true);
	}
	else if (KEY_PRESSED(KEY::UP))
		vPos.y += m_Speed * DT;
	else if (KEY_RELEASED(KEY::UP))
		Animator2D()->Play(0, 3, true);
	
	if (KEY_TAP(KEY::DOWN))
	{
		//Animator2D()->Play(1, 10, true);
	}
	else if (KEY_PRESSED(KEY::DOWN))
		vPos.y -= m_Speed * DT;
	else if (KEY_RELEASED(KEY::DOWN))
		Animator2D()->Play(0, 3, true);

	if (KEY_TAP(KEY::SPACE))
	{
		if (nullptr != m_MissilePref)
			Instantiate(m_MissilePref, 5, Transform()->GetWorldPos(), L"Missile");
	}

	if (KEY_PRESSED(KEY::Z))
	{
		//MeshRender()->GetMaterial()->SetScalarParam(INT_0, 1);

		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.z += XM_PI * DT;
		Transform()->SetRelativeRotation(vRot);
	}

	else
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_0, 0);
	}

	if (KEY_TAP(KEY::C))
	{
		Rigidbody()->Jump();
	}

	Transform()->SetRelativePos(vPos);
}

void CPlayerScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Speed, sizeof(float), 1, _pFile);
}

void CPlayerScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Speed, sizeof(float), 1, _pFile);
}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	//if (L"Monster" == _OtherObj->GetName())
	//{
	//	DeleteObject(_OtherObj);
	//}
}
