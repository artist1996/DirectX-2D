#pragma once
#include "CEntity.h"
class CAsset :
    public CEntity
{
private:
    wstring     m_Key;
    wstring     m_RelativePath;

    ASSET_TYPE  m_Type;

public:
    const wstring& GetKey()          { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }
    
private:
    void SetKey(const wstring& _Key)          { m_Key = _Key; }
    void SetRelativePath(const wstring _Path) { m_RelativePath = _Path; }

public:
    virtual void Binding() PURE;
    virtual CAsset* Clone() { return nullptr; }

public:
    CAsset(ASSET_TYPE _Type);
    virtual ~CAsset();

    friend class CAssetMgr;
};