#pragma once
#include "CComponent.h"

class CLight2D :
    public CComponent
{
private:
    tLightInfo m_Info;
    

public:
    void SetRadius(float _Radius)       { m_Info.Radius = _Radius; }
    void SetAngle(float _Angle)         { m_Info.Angle = _Angle; }
    void SetLightType(LIGHT_TYPE _Type) { m_Info.Type = _Type; }
    void SetColor(Vec4 _Color)       { m_Info.Info.Color = _Color; }

    const tLightInfo& GetLightInfo() { return m_Info; }
    float GetRadius()                { return m_Info.Radius; }
    float GetAngle()                 { return m_Info.Angle; }
    LIGHT_TYPE GetLightType()        { return m_Info.Type; }

public:
    virtual void FinalTick() override;

public:
    CLONE(CLight2D);
    CLight2D();
    virtual ~CLight2D();
};

