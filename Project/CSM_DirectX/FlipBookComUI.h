#pragma once
#include "ComponentUI.h"
class FlipBookComUI :
    public ComponentUI
{
private:

public:
    virtual void Update() override;

private:
    void SelectFlipBook(DWORD_PTR _ListUI);

public:
    FlipBookComUI();
    virtual ~FlipBookComUI();
};

