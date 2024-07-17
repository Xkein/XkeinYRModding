#include "editor/object_inspector.h"
#include "core/reflection/reflection.h"
#include "yr/api/yr_entity.h"
#include <FootClass.h>
#include <ObjectClass.h>

void YrObjectInspector::OnOpen()
{
    
}

void YrObjectInspector::OnClose()
{
    
}

void InspectObject(AbstractClass* pObject)
{
    entt::meta_type meta = GetYrClassMeta(pObject);

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable))
    {
        for (auto&& [id, field] : meta.data())
        {
            // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
            ImGui::PushID(id);

            // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            bool node_open = ImGui::TreeNode("Object", pObject->GetClassName());
            ImGui::TableSetColumnIndex(1);

            if (node_open)
            {
                static float placeholder_members[8] = { 0.0f, 0.0f, 1.0f, 3.1416f, 100.0f, 999.0f };
                for (int i = 0; i < 8; i++)
                {
                    ImGui::PushID(i); // Use field index as identifier.
                    // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::AlignTextToFramePadding();
                    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
                    ImGui::TreeNodeEx("Field", flags, "Field_%d", i);

                    ImGui::TableSetColumnIndex(1);
                    ImGui::SetNextItemWidth(-FLT_MIN);
                    ImGui::InputFloat("##value", &placeholder_members[i], 1.0f);
                    ImGui::NextColumn();
                    ImGui::PopID();
                }
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();
}

void YrObjectInspector::OnFrame()
{
    for (ObjectClass* pObject : ObjectClass::CurrentObjects.get())
    {
        InspectObject(pObject);
        break;
    }
}
