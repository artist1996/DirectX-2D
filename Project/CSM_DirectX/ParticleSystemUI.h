#pragma once
#include "ComponentUI.h"
class ParticleSystemUI :
    public ComponentUI
{
private:
    void Spawn();
    void Spawn_Burst();

public:
    virtual void Update() override;

public:
    ParticleSystemUI();
    virtual ~ParticleSystemUI();
};

