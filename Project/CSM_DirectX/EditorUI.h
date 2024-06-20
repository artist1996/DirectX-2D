#pragma once

class EditorUI
{
private:
	static UINT	      m_GlobalID;

	const UINT		  m_ID;
	string			  m_Name;
	string			  m_FullName;
	
	EditorUI*		  m_Parent;
	vector<EditorUI*> m_vecChildren;

	bool			  m_Active;

public:
	void AddChild(EditorUI* _UI);

	bool IsActive()   { return m_Active; }
	void Activate()   { m_Active = true; }
	void Deactivate() { m_Active = false; }

	void SetName(const string& _strName);

	const string& GetName()		{ return m_Name; }
	const string& GetFullName() { return m_FullName; }

public:
	virtual void Tick();
	virtual void Update() PURE;

public:
	EditorUI();
	virtual ~EditorUI();
};

