#pragma once
#include "TE_Sub.h"
class TE_TextureView :
    public TE_Sub
{
private:
    ImVec2  m_ImageRectMin;

private:
    void ClickedCheck();

public:
    virtual void Init() override;
    virtual void Update() override;

public:
    TE_TextureView();
    virtual ~TE_TextureView();
};

