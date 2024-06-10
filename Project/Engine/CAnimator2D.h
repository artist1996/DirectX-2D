#pragma once
#include "CComponent.h"

class CAnimator2D :
    public CComponent
{
private:
    map<wstring, CFlipBook*> m_mapAnim; // Animator2D 컴포넌트가 보유한 모든 FlipBook 목록
    CFlipBook*               m_CurAnim; // 현재 재생중인 FlipBook
    int                      m_CurIdx;  // 현재 재생중인 FlibBook 에서 몇번 째 Sprite 가 재생중인지 인덱스 기록

public:
    virtual void FinalTick() override;

public:
    CLONE(CAnimator2D);
    CAnimator2D();
    virtual ~CAnimator2D();
};

