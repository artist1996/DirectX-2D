#pragma once
#include "CComponent.h"
class CCollider2D :
    public CComponent
{
private:
    Vec3    m_Offset;
    Vec3    m_Scale;       // ���� or ���� ũ��
    Matrix  m_matColWorld; // �浹ü�� ���� ���� ����
    int     m_OverlapCount;

    bool    m_IndependentScale; // ������Ʈ�� ũ�⿡ ������ ������ ����
    
public:
    virtual void FinalTick() override;

public:
    void SetOffset(Vec3 _Offset)        { m_Offset = _Offset; }
    void SetScale(Vec3 _Scale)          { m_Scale = _Scale; }
    void SetIndependentScale(bool _Set) { m_IndependentScale = _Set; }
    
    Vec3 GetOffset()    { return m_Offset; }
    Vec3 GetScale()     { return m_Scale; }
    //Vec3 GetFinalPos()  { return m_FinalPos; }

    int GetOverlapCount() { return m_OverlapCount; }

public:
    void BeginOverlap(CCollider2D* _OtherCollider);
    void Overlap(CCollider2D* _OtherCollider);
    void EndOverlap(CCollider2D* _OtherCollider);

public:
    CLONE(CCollider2D);
    CCollider2D();
    virtual ~CCollider2D();
};

