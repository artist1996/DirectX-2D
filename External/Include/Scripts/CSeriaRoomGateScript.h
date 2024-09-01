#pragma once
#include <Engine/CScript.h>

class CSeriaRoomGateScript :
    public CScript
{
private:

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CSeriaRoomGateScript);
    CSeriaRoomGateScript();
    virtual ~CSeriaRoomGateScript();
};

