#pragma once
#include "TE_Sub.h"
class TE_TextureView :
    public TE_Sub
{
private:
    
public:
    virtual void Init() override;
    virtual void Update() override;

public:
    TE_TextureView();
    virtual ~TE_TextureView();
};

