#pragma once
#include "CRenderComponent.h"

#include "CParticleTickCS.h"

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer*   m_ParticleBuffer;
    Ptr<CParticleTickCS> m_TickCS;
    int                  m_MaxParticleCount;

public:
    virtual void FinalTick() override;
    virtual void Render()    override;
    virtual void SaveToFile(FILE* _File)   override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CParticleSystem);
    CParticleSystem();
    virtual ~CParticleSystem();
};

