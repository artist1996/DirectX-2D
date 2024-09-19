#include "pch.h"
#include "CPistolScript.h"

CPistolScript::CPistolScript()
	: CScript(SCRIPT_TYPE::PISTOLSCRIPT)
	, m_Speed(1000.f)
{
}

CPistolScript::~CPistolScript()
{
}

void CPistolScript::Begin()
{
	Animator2D()->Play(0, 10.f, true);
	Collider2D()->SetRender(true);

	if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
}

void CPistolScript::Tick()
{
	Vec3 vPos = GetOwner()->GetParent()->Transform()->GetRelativePos();
	Vec3 vInitPos = GetOwner()->GetParent()->GetInitPos();

	switch (GetOwner()->GetParent()->GetDir())
	{
	case OBJ_DIR::DIR_LEFT:
		vPos.x -= m_Speed * DT;
		break;

	case OBJ_DIR::DIR_RIGHT:
		vPos.x += m_Speed * DT;
		break;
	}

	if (650.f < fabs(vPos.x - vInitPos.x))
	{
		DeleteObject(GetOwner()->GetParent());
	}


	GetOwner()->GetParent()->Transform()->SetRelativePos(vPos);
}

void CPistolScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CPistolScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx() || L"Platform" == _OtherObj->GetName())
	{
		Vec3 vPos = Transform()->GetWorldPos();
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();

		if (GetOwner()->GetParent()->GetGroundCollision())
		{
			INFO& info = _OtherObj->GetInfo();

			if (L"hyungteo" == _OtherObj->GetName())
			{
				if (!_OtherObj->Rigidbody()->IsGround())
				{
					_OtherObj->Rigidbody()->SetGround(true);
					_OtherObj->FSM()->ChangeState(L"AirHit");
				}
			}
			else if (L"direzie" == _OtherObj->GetName() && !info.bSuperArmor)
			{
				if (_OtherObj->Rigidbody()->IsGround())
					_OtherObj->FSM()->ChangeState(L"GroundHit");
				else
				{
					_OtherObj->Rigidbody()->SetGround(true);
					_OtherObj->FSM()->ChangeState(L"Fall");
				}
			}

			info.HP -= 10.f;
			DeleteObject(GetOwner()->GetParent());
			GetOwner()->GetParent()->SetGroundCollision(false);
		}
	}
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

