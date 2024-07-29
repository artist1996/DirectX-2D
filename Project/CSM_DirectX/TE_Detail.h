#pragma once
#include "TE_Sub.h"
class TE_Detail :
    public TE_Sub
{
private:

private:
    void Texture();

private:
    void SelectTexture(DWORD_PTR _Param);

public:
    virtual void Init() override;
    virtual void Update() override;

public:
    TE_Detail();
    virtual ~TE_Detail();
};

