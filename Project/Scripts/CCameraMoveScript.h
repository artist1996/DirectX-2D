#pragma once
#include <Engine/CScript.h>

class CCameraMoveScript :
    public CScript
{
private:
    CGameObject* m_Target;

    float        m_CamSpeed;
    float        m_Dir;
    float        m_ShakingTime;

    Vec2         m_BoundaryLT;
    Vec3         m_StartPos;
    float        m_BoundaryRightWidth;
    float        m_BoundaryBottomHeight;

    bool         m_TargetMove;
    bool         m_Shaking;
  
private:
    void OrthoGraphicMove();
    void PerspectiveMove();

public:
    void SetShaking(bool _Set);

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CCameraMoveScript);
    CCameraMoveScript();
    virtual ~CCameraMoveScript();
};

