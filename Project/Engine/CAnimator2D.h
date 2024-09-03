#pragma once
#include "CComponent.h"

#include "CAnimation.h"

class CAnimator2D :
    public CComponent
{
private:
    vector<Ptr<CAnimation>>   m_vecAnimation;  // Animator2D ������Ʈ�� ������ ��� FlipBook ���
    Ptr<CAnimation>           m_CurAnimation;  // ���� ������� FlipBook
    Ptr<CSprite>              m_CurFrmSprite; // ���� ������� FlipBook ���� ���� ������ �ε����� �ش��ϴ� ��������Ʈ

    int                       m_CurFrmIdx;    // ���� ������� FlibBook ���� ��� ° Sprite �� ��������� �ε��� ���
    int                       m_MaxFrm;       // ���� ������� FlipBook �� �ִ� ������

    float                     m_FPS;          // ���� ������� FlipBook �� �ʴ� ������ ���� ��
    float                     m_AccTime;      // ���� �ð��� üũ

    bool                      m_Repeat;       // �ݺ� ��� ����
    bool                      m_Finish;       // FlipBook ����� ���� �����ߴ��� ����

public:
    void AddAnimation(int _Idx, Ptr<CAnimation> _FlipBook);
    Ptr<CAnimation> FindAnimation(const wstring& _Key);
    void Play(int _FlipBookIdx, float _FPS, bool _Repeat);
    void Stop();
    void Reset();
    void Binding();
    
    void erase(int _Idx);
    
    void SetCurAnimation(Ptr<CAnimation> _FlipBook) { m_CurAnimation = _FlipBook; }
    void SetFPS(float _FPS) { m_FPS = _FPS; }
    float GetFPS()          { return m_FPS; }
    bool IsFinish()         { return m_Finish; }

    static void Clear();

public:
    Ptr<CSprite>   GetCurSprite()                   { return m_CurFrmSprite; }
    Ptr<CAnimation> GetAnimationByIndex(int _Idx)   { return m_vecAnimation[_Idx]; }
    int            GetAnimationsSize()              { return (int)m_vecAnimation.size(); }
    Ptr<CAnimation> GetCurAnimation()               { return m_CurAnimation; }
    const vector<Ptr<CAnimation>> GetAnimations()   { return m_vecAnimation; }

    int GetCurFrameIndex() { return m_CurFrmIdx; }

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    virtual void FinalTick() override;

public:
    CLONE(CAnimator2D);
    CAnimator2D();
    CAnimator2D(const CAnimator2D& _Origin);
    virtual ~CAnimator2D();
};

