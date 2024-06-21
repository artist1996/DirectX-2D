#pragma once

#include "EditorUI.h"

class Outliner :
    public EditorUI
{
private:

public:
    virtual void Update() override;

public:
    Outliner();
    virtual ~Outliner();
};

