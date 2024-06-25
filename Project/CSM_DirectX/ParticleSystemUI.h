#pragma once
#include "ComponentUI.h"
class ParticleSystemUI :
    public ComponentUI
{
private:

public:
    virtual void Update() override;

public:
    ParticleSystemUI();
    virtual ~ParticleSystemUI();
};

