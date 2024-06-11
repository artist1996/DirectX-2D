#pragma once
#include "CEntity.h"
#include "CGameObject.h"

#define GET_OTHER_COMPONENT(Type) C##Type* Type() { return m_Owner->Type(); }

class CComponent :
    public CEntity
{
private:
    CGameObject*         m_Owner;
    const COMPONENT_TYPE m_Type;
    
public:
    COMPONENT_TYPE GetComponentType() { return m_Type; }
    CGameObject* GetOwner() { return m_Owner; }

public:
    virtual void Begin();
    virtual void Tick();
    virtual void FinalTick() PURE;

    GET_OTHER_COMPONENT(Transform);
    GET_OTHER_COMPONENT(MeshRender);
    GET_OTHER_COMPONENT(Camera);
    GET_OTHER_COMPONENT(Collider2D);
    GET_OTHER_COMPONENT(FlipBookComponent);

private:
    void SetOwner(CGameObject* _Object) { m_Owner = _Object; }

public:
    virtual CComponent* Clone() PURE;
    CComponent(COMPONENT_TYPE _Type);
    virtual ~CComponent();

    friend class CGameObject;
};

