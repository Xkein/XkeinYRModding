#pragma once
#include "editor/editor.h"

class YrObjectInspector : public YrEditorWindow
{
    virtual void OnOpen() override;
    virtual void OnClose() override;
    virtual void OnFrame() override;

public:
    YrObjectInspector();
    virtual ~YrObjectInspector();
    
};
