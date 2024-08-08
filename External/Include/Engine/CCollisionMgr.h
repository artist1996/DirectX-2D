#pragma once
#include "singleton.h"

class CCollider2D;

union COLLIDER_ID
{
	struct {
		DWORD LeftID;
		DWORD RightID;
	};
	ULONGLONG ID;
};


class CCollisionMgr :
    public CSingleton<CCollisionMgr>
{
    SINGLE(CCollisionMgr);

private:
	UINT					m_Matrix[MAX_LAYER];

	// ������ �浹ü�� ���� �������� �浹���̾������� ���� ������ �����ϰ� �־�� �Ѵ�.	
	map<ULONGLONG, bool>	m_mapCollisionInfo;
    
public:
	UINT* GetCollisionMatrix() { return m_Matrix; }

public:
	void CollisionCheck(UINT _Layer1, UINT _Layer2);
	void CollisionUnCheck(UINT _Layer1, UINT _Layer2);
	void CollisionCheckClear() { memset(m_Matrix, 0, sizeof(UINT) * MAX_LAYER); }
	void SetCollisionMatrix(UINT* _Matrix);

private:
	bool IsCollision(CCollider2D* _Left, CCollider2D* _Right);
	void CollisionBtwLayer(UINT _Left, UINT _Right);

public:
    void Tick();
};

