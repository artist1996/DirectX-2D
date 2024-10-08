#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CScript;
class CState;

#define GET_COMPONENT(Type, TYPE) class C##Type* Type() {return (C##Type*)GetComponent(COMPONENT_TYPE::TYPE);}

class CGameObject :
    public CEntity
{
private:
    CComponent*          m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*    m_RenderCom;
    vector<CScript*>     m_vecScript;
    vector<CState*>      m_vecState;
    
    CGameObject*         m_Parent;
    vector<CGameObject*> m_vecChildren;

    OBJ_DIR              m_Dir;
    OBJ_DIR              m_PrevDir;
    OBJ_DIR              m_TBDir;

    int                  m_LayerIdx;    // �Ҽ� ���̾��� �ε��� ��ȣ
    bool                 m_Dead;        // Object Dead

    Vec3                 m_InitPos;
    bool                 m_Moveable[(UINT)PLATFORM_TYPE::END];
    bool                 m_GroundCollision;
    bool                 m_Active;

    CGameObject*         m_Owner;
    CGameObject*         m_Target;

    OBJ_ID               m_ID;

    INFO                 m_Info;

    wstring              m_strFont;
    UINT                 m_Color;
    float                m_FontScale;
    Vec2                 m_FontOffset;

public:
    void AddComponent(CComponent* _Component);
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
    CRenderComponent* GetRenderComponent()         { return m_RenderCom; }

    CGameObject* GetParent()                  { return m_Parent; }
    const vector<CGameObject*>& GetChildren() { return m_vecChildren; }
    const vector<CScript*>& GetScripts()      { return m_vecScript; }

    CScript* FindScriptByName(const wstring& _strName);
    CGameObject* FindChildByName(const wstring& _strName);

    void ChangeLayer(CGameObject* _Object, int _Idx);
    int GetLayerIdx() { return m_LayerIdx; }
    void AddChild(CGameObject* _ChildObject);

    void SetMoveable(PLATFORM_TYPE _Type, bool _Set) { m_Moveable[(UINT)_Type] = _Set; }
    bool* GetMoveable()                              { return m_Moveable; }
   
    void SetMove(bool _Set)   { m_Info.bMoveable = _Set; }
    void  SetInfo(INFO _Info) { m_Info = _Info; }
    INFO& GetInfo()           { return m_Info; }

    void SetForce(bool _Set)  { m_Info.bForce = _Set; }
    
    void SetGroundCollision(bool _Set) { m_GroundCollision = _Set; }
    bool IsGroundCollision()          { return m_GroundCollision; }

    void SetActive(bool _Set);
    bool IsActive()           { return m_Active; }

    void DisconnectWithLayer();

    // Unregister : ����� ����ϴ�, ����ϴ� ������ ����ϴ�.
    // Deregister : ��ϵ� ���� ����ϴ�.
    void DeregisterChild();

    bool IsDead() { return m_Dead; }
    bool IsAncestor(CGameObject* _Object);

    void SetDir(OBJ_DIR _Dir)   { m_Dir = _Dir; }
    OBJ_DIR GetDir()            { return m_Dir; }

    void SetTBDir(OBJ_DIR _Dir) { m_TBDir = _Dir; }
    OBJ_DIR GetTBDir()          { return m_TBDir; }

    void SetPrevDir(OBJ_DIR _Dir) { m_PrevDir = _Dir; }
    OBJ_DIR GetPrevDir()          { return m_PrevDir; }

    void SetID(OBJ_ID _ID) { m_ID = _ID;  }
    OBJ_ID GetID()         { return m_ID; }

    void SetInitPos(Vec3 _Pos) { m_InitPos = _Pos; }
    Vec3 GetInitPos()          { return m_InitPos; }

    void SetOwner(CGameObject* _Owner) { m_Owner = _Owner; }
    CGameObject* Get_Owner()            { return m_Owner; }

    void SetTarget(CGameObject* _Target) { m_Target = _Target; }
    CGameObject* GetTarget()             { return m_Target; }

    void SetSpeed(float _Speed)          { m_Info.Speed = _Speed; }

    void SetFontScale(float _Scale)       { m_FontScale = _Scale; }
    void SetFont(const wstring& _strFont) { m_strFont = _strFont; }
    void SetFontColor(UINT _Color)        { m_Color = _Color; }
    void SetFontOffset(Vec2 _Offset)      { m_FontOffset = _Offset; }

    void SetLayerIdx(int _Idx) { m_LayerIdx = _Idx; }

    Vec3 CarculatePosition();

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(Collider2D, COLLIDER2D);
    GET_COMPONENT(Animator2D, ANIMATOR2D);
    GET_COMPONENT(TileMap, TILEMAP);
    GET_COMPONENT(Light2D, LIGHT2D);
    GET_COMPONENT(Rigidbody, RIGIDBODY);
    GET_COMPONENT(ParticleSystem, PARTICLESYSTEM);
    GET_COMPONENT(FSM, STATEMACHINE);

public:
    void Begin();
    void Tick();
    virtual void FinalTick();
    void Render();
    
public:
    virtual CGameObject* Clone() { return new CGameObject(*this); }
    CGameObject();
    CGameObject(const CGameObject& _Origin);
    virtual ~CGameObject();

    friend class CLevel;
    friend class CLayer;
    friend class CTaskMgr;
    friend class CObjectPoolMgr;
};