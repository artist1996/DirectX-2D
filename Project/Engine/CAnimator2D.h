#pragma once
#include "CComponent.h"

class CAnimator2D :
    public CComponent
{
private:
    map<wstring, CFlipBook*> m_mapAnim; // Animator2D ������Ʈ�� ������ ��� FlipBook ���
    CFlipBook*               m_CurAnim; // ���� ������� FlipBook
    int                      m_CurIdx;  // ���� ������� FlibBook ���� ��� ° Sprite �� ��������� �ε��� ���

public:
    virtual void FinalTick() override;

public:
    CLONE(CAnimator2D);
    CAnimator2D();
    virtual ~CAnimator2D();
};

