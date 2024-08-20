#pragma once
#include "ComponentUI.h"
class ParticleSystemUI :
    public ComponentUI
{
private:
    bool m_bChange;

private:
    void Spawn();
    void Spawn_Burst();

public:
    virtual void Update() override;

public:
    ParticleSystemUI();
    virtual ~ParticleSystemUI();
};

