#pragma once
#include "CComponent.h"

#include "CFlipBook.h"

class CFlipBookComponent :
    public CComponent
{
private:
    vector<Ptr<CFlipBook>>   m_vecAnimation;  // Animator2D ������Ʈ�� ������ ��� FlipBook ���
    Ptr<CFlipBook>           m_CurAnimation;  // ���� ������� FlipBook
    Ptr<CSprite>             m_CurFrmSprite; // ���� ������� FlipBook ���� ���� ������ �ε����� �ش��ϴ� ��������Ʈ

    int                      m_CurFrmIdx;    // ���� ������� FlibBook ���� ��� ° Sprite �� ��������� �ε��� ���
    int                      m_MaxFrm;       // ���� ������� FlipBook �� �ִ� ������

    float                    m_FPS;          // ���� ������� FlipBook �� �ʴ� ������ ���� ��
    float                    m_AccTime;      // ���� �ð��� üũ

    bool                     m_Repeat;       // �ݺ� ��� ����
    bool                     m_Finish;       // FlipBook ����� ���� �����ߴ��� ����

public:
    void AddFlipBook(int _Idx, Ptr<CFlipBook> _FlipBook);
    Ptr<CFlipBook> FindFlipBook(const wstring& _Key);
    void Play(int _FlipBookIdx, float _FPS, bool _Repeat);
    void Reset();
    void Binding();
    
    void SetCurFlipBook(Ptr<CFlipBook> _FlipBook) { m_CurAnimation = _FlipBook; }
    void SetFPS(float _FPS) { m_FPS = _FPS; }
    float GetFPS()          { return m_FPS; }
    
    static void Clear();

public:
    Ptr<CSprite>   GetCurSprite()               { return m_CurFrmSprite; }
    Ptr<CFlipBook> GetFlipBookByIndex(int _Idx) { return m_vecAnimation[_Idx]; }
    int            GetFlipBookSize()            { return (int)m_vecAnimation.size(); }
    Ptr<CFlipBook> GetCurFlipBook()             { return m_CurAnimation; }
    const vector<Ptr<CFlipBook>> GetFlipBook()  { return m_vecAnimation; }

    int GetCurFrameIndex() { return m_CurFrmIdx; }

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    virtual void FinalTick() override;

public:
    CLONE(CFlipBookComponent);
    CFlipBookComponent();
    CFlipBookComponent(const CFlipBookComponent& _Origin);
    virtual ~CFlipBookComponent();
};

