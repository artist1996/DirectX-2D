#pragma once
#include "CComponent.h"

class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh>          m_Mesh;
    Ptr<CMaterial>      m_Mtrl;         // ���� ������� ����
    Ptr<CMaterial>      m_SharedMtrl;   // ���� ����(������)
    Ptr<CMaterial>      m_DynamicMtrl;  // �ӽ� ����

public:
    void SetMesh(Ptr<CMesh> _Mesh)  { m_Mesh = _Mesh; }
    void SetMaterial(Ptr<CMaterial> _Mtrl);

    Ptr<CMesh> GetMesh()            { return m_Mesh; }
    Ptr<CMaterial> GetMaterial()    { return m_Mtrl; }
    Ptr<CMaterial> GetSharedMaterial();
    Ptr<CMaterial> GetDynamicMaterial();

public:
    virtual void FinalTick() PURE;
    virtual void Render() PURE;
    virtual CRenderComponent* Clone() PURE;

public:
    void SaveDataToFile(FILE* _pFile);
    void LoadDataFromFile(FILE* _pFile);

public:
    CRenderComponent(COMPONENT_TYPE _Type);
    CRenderComponent(const CRenderComponent& _Origin);
    virtual ~CRenderComponent();
};