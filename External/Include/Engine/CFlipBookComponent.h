#pragma once
#include "CComponent.h"

#include "CFlipBook.h"

class CFlipBookComponent :
    public CComponent
{
private:
    vector<Ptr<CFlipBook>>   m_vecFlipBook; // Animator2D 컴포넌트가 보유한 모든 FlipBook 목록
    Ptr<CFlipBook>           m_CurFlipBook; // 현재 재생중인 FlipBook
    Ptr<CSprite>             m_CurFrmSprite;

    int                      m_CurFrmIdx;   // 현재 재생중인 FlibBook 에서 몇번 째 Sprite 가 재생중인지 인덱스 기록
    int                      m_MaxFrm;

    float                    m_FPS;  
    float                    m_AccTime;

    bool                     m_Repeat;
    bool                     m_Finish;

public:
    void AddFlipBook(Ptr<CFlipBook> _FlipBook) { m_vecFlipBook.push_back(_FlipBook); }
    Ptr<CFlipBook> FindFlipBook(const wstring& _Key);
    void Play(int _FlipBookIdx, float _FPS, bool _Repeat);
    void Reset();

public:
    Ptr<CSprite> GetCurSprite() { return m_CurFrmSprite; }

public:
    virtual void FinalTick() override;

public:
    CLONE(CFlipBookComponent);
    CFlipBookComponent();
    virtual ~CFlipBookComponent();
};

