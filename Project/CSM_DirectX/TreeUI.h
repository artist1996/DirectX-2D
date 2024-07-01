#pragma once
#include "EditorUI.h"

class TreeNode
{
private:
    string            m_strName;
    TreeNode*         m_ParentNode;
    vector<TreeNode*> m_vecChildNode;


public:
    void SetName(const string& _strName) { m_strName = _strName; }
    const string& GetName()              { return m_strName; }

    void AddChildNode(TreeNode* _Node);
    void Update();

public:
    TreeNode();
    ~TreeNode();
};

class TreeUI :
    public EditorUI
{
private:
    TreeNode* m_Root;

public:
    virtual void Update() override;

    void AddNode(const string& _strName);

public:
    TreeUI();
    virtual ~TreeUI();
};

