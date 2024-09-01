#include "editor/editor_module.h"
#include "codegen/XkeinEditor.gen.h"

void YrXkeinEditorModule::Startup()
{
    __Gen_Type_XkeinEditor::Register();

}

void YrXkeinEditorModule::Shutdown()
{

    __Gen_Type_XkeinEditor::Unregister();
}
