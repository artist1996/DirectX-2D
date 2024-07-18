#pragma once
#include "CComponent.h"

#include "CFlipBook.h"

class CFlipBookComponent :
    public CComponent
{
private:
    vector<Ptr<CFlipBook>>   m_vecFlipBook;  // Animator2D 컴포넌트가 보유한 모든 FlipBook 목록
    Ptr<CFlipBook>           m_CurFlipBook;  // 현재 재생중인 FlipBook
    Ptr<CSprite>             m_CurFrmSprite; // 현재 재생중인 FlipBook 에서 현재 프레임 인덱스에 해당하는 스프라이트

    int                      m_CurFrmIdx;    // 현재 재생중인 FlibBook 에서 몇번 째 Sprite 가 재생중인지 인덱스 기록
    int                      m_MaxFrm;       // 현재 재생중인 FlipBook 의 최대 프레임

    float                    m_FPS;          // 현재 재생중인 FlipBook 의 초당 프레임 진행 수
    float                    m_AccTime;      // 누적 시간값 체크

    bool                     m_Repeat;       // 반복 재생 여부
    bool                     m_Finish;       // FlipBook 재생이 끝에 도달했는지 여부

public:
    void AddFlipBook(int _Idx, Ptr<CFlipBook> _FlipBook);
    Ptr<CFlipBook> FindFlipBook(const wstring& _Key);
    void Play(int _FlipBookIdx, float _FPS, bool _Repeat);
    void Reset();
    void Binding();
    
    void SetCurFlipBook(Ptr<CFlipBook> _FlipBook) { m_CurFlipBook = _FlipBook; }

    static void Clear();

public:
    Ptr<CSprite>   GetCurSprite()               { return m_CurFrmSprite; }
    Ptr<CFlipBook> GetFlipBookByIndex(int _Idx) { return m_vecFlipBook[_Idx]; }
    size_t         GetFlipBookSize()            { return m_vecFlipBook.size(); }
    Ptr<CFlipBook> GetCurFlipBook()             { return m_CurFlipBook; }
    const vector<Ptr<CFlipBook>> GetFlipBook() { return m_vecFlipBook; }

    int GetCurFrameIndex() { return m_CurFrmIdx; }

public:
    virtual void FinalTick() override;

public:
    CLONE(CFlipBookComponent);
    CFlipBookComponent();
    CFlipBookComponent(const CFlipBookComponent& _Origin);
    virtual ~CFlipBookComponent();
};

