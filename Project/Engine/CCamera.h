#pragma once
#include "CComponent.h"

enum PROJ_TYPE
{
    ORTHOGRAPHIC,       // ���� ����
    PERSPECTIVE,        // ���� ����
};

class CCamera :
    public CComponent
{
private:
    int       m_Priority;

    UINT      m_LayerCheck; // ���ϴ� ���̾ ī�޶� �������� ����

    PROJ_TYPE m_ProjType;

    float     m_Width;
    float     m_Height;
    float     m_Far;        // ī�޶� �ٶ� �� �ִ� z���� �Ÿ�

    float     m_FOV;        // Field Of View (�þ� ����, �þ� ��) ���� ���� ��

    Matrix    m_matView;
    Matrix    m_matProj;

public:
    void SetPriority(int _Priority) { m_Priority = _Priority; }
    void SetLayer(UINT _LayerIdx, bool _bCheck)
    {
        if (_bCheck)
            m_LayerCheck |= (1 << _LayerIdx);

        else
            m_LayerCheck &= ~(1 << _LayerIdx);
    }

    void SetLayerAll()                { m_LayerCheck = 0xffffffff; }
    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }
    void SetFar(float _Far)           { m_Far = _Far; }

    PROJ_TYPE GetProjType() { return m_ProjType; }
    float GetFar()          { return m_Far; }
    

public:
    virtual void Begin() override;
    virtual void FinalTick() override;
    void Render();

public:
    CLONE(CCamera);
    CCamera();
    virtual ~CCamera();
};

