#include "pch.h"
#include "CPistolScript.h"

CPistolScript::CPistolScript()
	: CScript(SCRIPT_TYPE::PISTOLSCRIPT)
	, m_Speed(50.f)
	, m_Dir(DIR_LEFT)
{
}

CPistolScript::~CPistolScript()
{
}

void CPistolScript::Begin()
{
	Animator2D()->Play(0, 10.f, true);
	Collider2D()->SetActive(true);

	if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
}

void CPistolScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vInitPos = GetOwner()->GetInitPos();

	switch (GetOwner()->GetDir())
	{
	case OBJ_DIR::DIR_LEFT:
		vPos.x -= 1000.f * DT;
		break;

	case OBJ_DIR::DIR_RIGHT:
		vPos.x += 1000.f * DT;
		break;
	}

	if (650.f < fabs(vPos.x - vInitPos.x))
	{
		DeleteObject(GetOwner());
	}

	Transform()->SetRelativePos(vPos);
}

void CPistolScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"Monster" == _OtherObj->GetName())
	{
		DeleteObject(_OtherObj);
	}
}

void CPistolScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPistolScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPistolScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Speed, sizeof(float), 1, _pFile);
}

void CPistolScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Speed, sizeof(float), 1, _pFile);
}

