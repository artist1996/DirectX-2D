#pragma once
#include "EditorUI.h"

class TreeNode
{
private:
    class TreeUI*     m_Owner;
    string            m_strName;
    TreeNode*         m_ParentNode;
    vector<TreeNode*> m_vecChildNode;

    const UINT        m_ID;
    DWORD_PTR         m_Data;

    bool              m_Frame;
    bool              m_Selected;

public:
    void SetName(const string& _strName) { m_strName = _strName; }
    const string& GetName()              { return m_strName; }

    void AddChildNode(TreeNode* _Node);
    void Update();

    void SetFrame(bool _Frame) { m_Frame = _Frame; }
    bool IsFrame()             { return m_Frame; }

    DWORD_PTR GetData()        { return m_Data; }

public:
    TreeNode(UINT _ID);
    ~TreeNode();

    friend class TreeUI;
};

class TreeUI :
    public EditorUI
{
private:
    TreeNode*  m_Root;
    TreeNode*  m_SelectedNode;
    
    UINT       m_NodeID;
    bool       m_ShowRoot;

    EditorUI*  m_ClickedInst;
    DELEGATE_1 m_ClickedFunc;

public:
    virtual void Update() override;

    TreeNode* AddNode(TreeNode* _Parent, const string& _strName, DWORD_PTR _Data = 0);
    void SetSelectedNode(TreeNode* _Node);
    void SetShowRoot(bool _Show) { m_ShowRoot = _Show; }
    bool IsShowRoot()            { return m_ShowRoot; }

    void AddClickedDelegate(EditorUI* _Inst, DELEGATE_1 _Func) { m_ClickedInst = _Inst; m_ClickedFunc = _Func; }
    void Clear();

public:
    TreeUI();
    virtual ~TreeUI();
};