#pragma once
#include "CEntity.h"

#include "CFSM.h"

class CState :
    public CEntity
{
private:
    CFSM* m_Owner;
    UINT  m_Type;
    
protected:
    CGameObject* GetOwner() { return m_Owner->GetOwner(); }
    CFSM*        GetFSM()   { return m_Owner; }

public:
    UINT GetStateType() { return m_Type; }

public:
    virtual void Enter()     PURE;
    virtual void FinalTick() PURE;
    virtual void Exit()      PURE;

public:
    CState(UINT _Type);
    virtual ~CState();

    friend class CFSM;
};

