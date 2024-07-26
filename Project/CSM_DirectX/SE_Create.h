#pragma once
#include "SE_Sub.h"


class SE_Create :
    public SE_Sub
{
private:
    Ptr<CTexture> m_Texture;
    Vec2          m_LT;
    Vec2          m_Slice;

    string        m_strName;

public:
    virtual void Init() override;
    virtual void Update() override;

public:
    void SetTexture(Ptr<CTexture> _Texture) { m_Texture = _Texture; }
    void SetInfo(Vec2 _LT, Vec2 _Slice)     { m_LT = _LT; m_Slice = _Slice; }

public:
    virtual void Activate() override;
    virtual void Deactivate() override;

public:
    SE_Create();
    virtual ~SE_Create();
};

