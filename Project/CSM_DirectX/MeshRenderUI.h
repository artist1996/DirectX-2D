#pragma once
#include "ComponentUI.h"
class MeshRenderUI :
    public ComponentUI
{
private:

public:
    virtual void Update() override;

public:
    MeshRenderUI();
    virtual ~MeshRenderUI();
};

