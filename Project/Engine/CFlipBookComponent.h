#pragma once
#include "CComponent.h"

#include "CFlipBook.h"

class CFlipBookComponent :
    public CComponent
{
private:
    vector<Ptr<CFlipBook>>   m_vecFlipBook;  // Animator2D ������Ʈ�� ������ ��� FlipBook ���
    Ptr<CFlipBook>           m_CurFlipBook;  // ���� ������� FlipBook
    Ptr<CSprite>             m_CurFrmSprite; // ���� ������� FlipBook ���� ���� ������ �ε����� �ش��ϴ� ��������Ʈ

    int                      m_CurFrmIdx;    // ���� ������� FlibBook ���� ��� ° Sprite �� ��������� �ε��� ���
    int                      m_MaxFrm;       // ���� ������� FlipBook �� �ִ� ������

    float                    m_FPS;          // ���� ������� FlipBook �� �ʴ� ������ ���� ��
    float                    m_AccTime;      // ���� �ð��� üũ

    bool                     m_Repeat;       // �ݺ� ��� ����
    bool                     m_Finish;       // FlipBook ����� ���� �����ߴ��� ����

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

