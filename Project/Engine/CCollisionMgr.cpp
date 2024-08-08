#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CAssetMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CGameObject.h"
#include "CCollider2D.h"

#include "CMesh.h"

CCollisionMgr::CCollisionMgr()
    : m_Matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Tick()
{
	for (int Row = 0; Row < MAX_LAYER; ++Row)
	{
        for (int Col = Row; Col < MAX_LAYER; ++Col)
        {
            if (m_Matrix[Row] & (1 << Col))
            {
				CollisionBtwLayer(Row, Col);
            }
        }
	}
}

void CCollisionMgr::CollisionCheck(UINT _Layer1, UINT _Layer2)
{
    UINT Row = _Layer1;
    UINT Col = _Layer2;

    if (Row > Col)
    {
        Row = _Layer2;
        Col = _Layer1;
    }

    if (Row & (1 << Col))
    {
        m_Matrix[Row] &= ~(1 << Col);
    }

    else
    {
		m_Matrix[Row] |= (1 << Col);
    }
}

void CCollisionMgr::CollisionUnCheck(UINT _Layer1, UINT _Layer2)
{
	UINT Row = _Layer1;
	UINT Col = _Layer2;

	if (Row > Col)
	{
		Row = _Layer2;
		Col = _Layer1;
	}

	m_Matrix[Row] &= ~(1 << Col);	
}

void CCollisionMgr::SetCollisionMatrix(UINT* _Matrix)
{
	CollisionCheckClear();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Matrix[i] = _Matrix[i];
	}
}

void CCollisionMgr::CollisionBtwLayer(UINT _Left, UINT _Right)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	if (nullptr == pCurLevel)
		return;

	const vector<CGameObject*>& vecLeft = pCurLevel->GetLayer(_Left)->GetObjects();
	const vector<CGameObject*>& vecRight = pCurLevel->GetLayer(_Right)->GetObjects();

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		CCollider2D* pLeftCol = vecLeft[i]->Collider2D();

		if (nullptr == pLeftCol)
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			CCollider2D* pRightCol = vecRight[j]->Collider2D();

			if (nullptr == pRightCol)
				continue;

			COLLIDER_ID id = {};

			id.LeftID = pLeftCol->GetID();
			id.RightID = pRightCol->GetID();

			map<ULONGLONG, bool>::iterator iter = m_mapCollisionInfo.find(id.ID);

			// ��ϵ����� ������ ��Ͻ�Ų��.
			if (iter == m_mapCollisionInfo.end())
			{
				m_mapCollisionInfo.insert(make_pair(id.ID, false));
				iter = m_mapCollisionInfo.find(id.ID);
			}

			bool bDead = pLeftCol->GetOwner()->IsDead() || pRightCol->GetOwner()->IsDead();
			//bool bDeactive = !vecLeft[i]->IsActive() || !vecRight[j]->IsActive();


			// �� �浹ü�� ���� �浹���̴�.
			if (IsCollision(pLeftCol, pRightCol))
			{
				// �������� �浹���̾���.
				if (iter->second)
				{
					pLeftCol->Overlap(pRightCol);
					pRightCol->Overlap(pLeftCol);
				}

				// �������� �浹���� �ƴϾ���.
				else
				{
					pLeftCol->BeginOverlap(pRightCol);
					pRightCol->BeginOverlap(pLeftCol);
				}

				iter->second = true;

				// �� �浹ü�� �ϳ��� Dead ���°ų� ��Ȱ��ȭ ���¶��
				// �߰��� �浹 ������ ȣ������ش�.
				if (bDead) //|| bDeactive)
				{
					pLeftCol->EndOverlap(pRightCol);
					pRightCol->EndOverlap(pLeftCol);
					iter->second = false;
				}
			}

			// �� �浹ü�� ���� �浹���� �ƴϴ�.
			else
			{
				// �������� �浹���̾���.
				if (iter->second)
				{
					pLeftCol->EndOverlap(pRightCol);
					pRightCol->EndOverlap(pLeftCol);
				}

				iter->second = false;
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider2D* _Left, CCollider2D* _Right)
{
	// �浹ü�� �⺻ ���� ������ ��������, Local Space ���� ���� ������ �����´�.
	Ptr<CMesh> pMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh");
	Vtx* pVtx = (Vtx*)pMesh->GetVtxSysMem();
	
	// �� �浹ü�� ���� ����� �����´�.
	const Matrix& matLeft = _Left->GetWorldMatrix();
	const Matrix& matRight = _Right->GetWorldMatrix();
	

	// �⺻ ����(Rect) �� �� �浹ü�� ��������� ���ؼ�, �浹ü�� �� �𼭸� ��ġ�� �ű� ��,
	// ��ǥ���� ��ġ���� ���� �浹ü�� ����󿡼��� ��ġ���� ������ ǥ�� ���⺤�͸� ���Ѵ�.
	// �� ���ʹ� �浹ü���� ������ų ���� �� ����
	// Local Space ���� World Space �� �̵��ؾ� �ϱ� ������ ������ǥ�� 1�� �̵��� ���� �޴� XMVector3Coord �Լ��� ��� �ؼ�
	// ���� Mesh�� LocalSpace �� �浹ü�� ��������� �����ְ� ���༭ ���� ���͸� ����Ѵ�. 
	Vec3 vProjAxis[4] = {};

	vProjAxis[0] = XMVector3TransformCoord(pVtx[3].vPos, matLeft) - XMVector3TransformCoord(pVtx[0].vPos, matLeft);
	vProjAxis[1] = XMVector3TransformCoord(pVtx[1].vPos, matLeft) - XMVector3TransformCoord(pVtx[0].vPos, matLeft);

	vProjAxis[2] = XMVector3TransformCoord(pVtx[3].vPos, matRight) - XMVector3TransformCoord(pVtx[0].vPos, matRight);
	vProjAxis[3] = XMVector3TransformCoord(pVtx[1].vPos, matRight) - XMVector3TransformCoord(pVtx[0].vPos, matRight);

	// �浹ü�� �߽��� �մ� ����
	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f,0.f,0.f), matLeft) - XMVector3TransformCoord(Vec3(0.f,0.f,0.f), matRight);

	// ����
	for (int i = 0; i < 4; ++i)
	{
		Vec3 vProj = vProjAxis[i];
		vProj.Normalize();

		// ������ ���� Scalar
		float Dot = fabs(vProjAxis[0].Dot(vProj));
		Dot += fabs(vProjAxis[1].Dot(vProj));
		Dot += fabs(vProjAxis[2].Dot(vProj));
		Dot += fabs(vProjAxis[3].Dot(vProj));
		Dot /= 2.f;
		
		float fCenter = fabs(vCenter.Dot(vProj));
		
		if (Dot < fCenter)
		{
			return false;
		}
	}
	
    return true;
}