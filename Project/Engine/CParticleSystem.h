#pragma once
#include "CRenderComponent.h"

#include "CParticleTickCS.h"

struct tSpawnCount
{
    UINT iSpawnCount;
    UINT Padding[3];
};

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    Ptr<CParticleTickCS> m_TickCS;

    CStructuredBuffer*   m_ParticleBuffer;      // ��� ��ƼŬ ����
    CStructuredBuffer*   m_SpawnCountBuffer;    // ��ƼŬ Ȱ��ȭ ���� ���޿� ����
    CStructuredBuffer*   m_ModuleBuffer;        // Module Data Buffer

    Ptr<CTexture>        m_ParticleTex;
    Ptr<CTexture>        m_EndTex;

    float                m_Time;                // ���� �ð�
    float                m_BurstTime;           // SpawnBurst üũ�� ����

    int                  m_MaxParticleCount;    // ��ƼŬ �ִ� ����

    tParticleModule      m_Module;              // ��ƼŬ�� ��� ����

    

public:
    void SetParticleTexture(Ptr<CTexture> _Texture) { m_ParticleTex = _Texture; }

    Ptr<CTexture>       GetParticleTex()      { return m_ParticleTex; }
    tParticleModule&    GetModuleInfo()       { return m_Module; }    
    int                 GetMaxParticleCount() { return m_MaxParticleCount; }
    
    UINT&               GetSpaceType()        { return m_Module.SpaceType; }

    void CreateModuleBuffer();

public:
    virtual void FinalTick() override;
    virtual void Render()    override;

    void CarculateSpawnCount();

    virtual void SaveToFile(FILE* _File)   override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CParticleSystem);
    CParticleSystem();
    CParticleSystem(const CParticleSystem& _Origin);
    virtual ~CParticleSystem();
};

