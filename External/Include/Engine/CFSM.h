#pragma once
#include "CComponent.h"

class CState;

class CFSM :
    public CComponent
{
private:
    map<wstring, CState*> m_mapState;
    CState*               m_CurState;

public:
    virtual void FinalTick() override;

public:
    void    AddState(const wstring& _strName, CState* _State);
    void    ChangeState(const wstring& _strName);
    CState* FindState(const wstring& _strName);

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CFSM);
    CFSM();
    virtual ~CFSM();
};