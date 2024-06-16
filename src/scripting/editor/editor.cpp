
#include "scripting/editor/graph/graph_editor.h"
#include "imgui_internal.h"
#include "editor.h"
std::shared_ptr<GraphEditor> editor;


void EngineEditor::Tick()
{

    if (ImGui::IsKeyReleased(ImGuiKey_F11))
    {
        if (editor)
        {
            editor.reset();
        }
        else
        {
            editor = std::make_shared<GraphEditor>();
        }
    }
}
