#pragma once
#include "ComponentUI.h"
class FlipBookComUI :
    public ComponentUI
{
private:
    UINT m_UIHeight;
    int  m_Idx;
    int  m_AddIdx;

public:
    virtual void Update() override;

private:
    void SelectFlipBook(DWORD_PTR _ListUI);
    

public:
    FlipBookComUI();
    virtual ~FlipBookComUI();
};

