#pragma once
#include "CComponent.h"

class CLight2D :
    public CComponent
{
private:
    tLightInfo      m_Info;

public:
    void SetLightType(LIGHT_TYPE _Type);
    void SetRadius(float _Radius)   { m_Info.Radius = _Radius; }
    void SetAngle(float _Angle)     { m_Info.Angle = _Angle; }
    void SetLightColor(Vec3 _Color) { m_Info.Info.Color = _Color; }
    void SetLightAmbient(Vec3 _Amb) { m_Info.Info.Ambient = _Amb; }

    LIGHT_TYPE GetLightType() { return m_Info.Type; }
    float GetRadius()         { return m_Info.Radius; }
    float GetAngle()          { return m_Info.Angle; }
    Vec3 GetLightColor()      { return m_Info.Info.Color; }
    Vec3 GetLightAmbient()    { return m_Info.Info.Ambient; }


    const tLightInfo& GetLightInfo() { return m_Info; }

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    virtual void FinalTick() override;

public:
    CLONE(CLight2D);
    CLight2D();
    virtual ~CLight2D();
};

