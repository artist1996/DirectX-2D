#pragma once
#include <Engine/CScript.h>

#include "CPanelScript.h"

typedef void(CScript::* DELEGATE_0)(void);
typedef void(CScript::* DELEGATE_1)(void);
typedef void(CScript::* DELEGATE_2)(void);

class CMouseScript :
    public CScript
{
private:
    Ptr<CTexture> m_NormalTex;
    Ptr<CTexture> m_ClickTex;

    CScript*     m_ClickInst;
    DELEGATE_0   m_ClickFunc;

    CScript*     m_PressedInst;
    DELEGATE_1   m_PressedFunc;

    CScript*     m_RbtnClickInst;
    DELEGATE_2   m_RbtnClickFunc;

    bool         m_Click;

public:
    void SetClickInst(CScript* _Inst)             { m_ClickInst = _Inst; }
    void SetClickDelegate(DELEGATE_0 _Func)       { m_ClickFunc = _Func; }

    void SetPressedInst(CScript* _Inst)           { m_PressedInst = _Inst; }
    void SetPressedDelegate(DELEGATE_1 _Func)     { m_PressedFunc = _Func; }

    void SetRbtnClickInst(CScript* _Inst)         { m_RbtnClickInst = _Inst; }
    void SetRbtnClickDelegate(DELEGATE_2 _Func)   { m_RbtnClickFunc = _Func; }

public:
    CScript* GetRbtnInst() { return m_RbtnClickInst; }
    CScript* GetLbtnInst() { return m_ClickInst; }

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CMouseScript);
    CMouseScript();
    virtual ~CMouseScript();
};

//typedef void(CScript::* DELEGATE_1)(DWORD_PTR);
//typedef void(CScript::* DELEGATE_2)(DWORD_PTR, DWORD_PTR);
//typedef void(CScript::* DELEGATE_3)(DWORD_PTR, DWORD_PTR, DWORD_PTR);