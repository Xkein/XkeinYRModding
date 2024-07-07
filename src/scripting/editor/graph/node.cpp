#include "scripting/editor/graph/node.h"
#include "scripting/editor/graph/graph.h"
#include "scripting/editor/graph/graph_editor.h"

void EdMetaCodeNode::OnDraw(EdGraphNodeDrawContext const& context)
{
    auto& node = *this;
    if (node.Type != NodeType::Blueprint && node.Type != NodeType::Simple)
        return;
    auto& builder     = *context.builder;
    auto  editor      = context.editor;
    auto  graph       = editor->m_graph;
    auto  newLinkPin  = context.newLinkPin;

    const auto isSimple = node.Type == NodeType::Simple;

    bool hasOutputDelegates = false;
    for (auto& output : node.Outputs)
        if (output.Type == PinType::Delegate)
            hasOutputDelegates = true;

    builder.Begin(node.ID);
    if (!isSimple)
    {
        builder.Header(node.Color);
        ImGui::Spring(0);
        ImGui::TextUnformatted(node.Name.c_str());
        ImGui::Spring(1);
        ImGui::Dummy(ImVec2(0, 28));
        if (hasOutputDelegates)
        {
            ImGui::BeginVertical("delegates", ImVec2(0, 28));
            ImGui::Spring(1, 0);
            for (auto& output : node.Outputs)
            {
                if (output.Type != PinType::Delegate)
                    continue;

                auto alpha = ImGui::GetStyle().Alpha;
                if (newLinkPin && ! graph->CanCreateLink(newLinkPin, &output) && &output != newLinkPin)
                    alpha = alpha * (48.0f / 255.0f);

                ed::BeginPin(output.ID, ed::PinKind::Output);
                ed::PinPivotAlignment(ImVec2(1.0f, 0.5f));
                ed::PinPivotSize(ImVec2(0, 0));
                ImGui::BeginHorizontal(output.ID.AsPointer());
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
                if (!output.Name.empty())
                {
                    ImGui::TextUnformatted(output.Name.c_str());
                    ImGui::Spring(0);
                }
                editor->DrawPinIcon(output, graph->IsPinLinked(output.ID), (int)(alpha * 255));
                ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.x / 2);
                ImGui::EndHorizontal();
                ImGui::PopStyleVar();
                ed::EndPin();

                // DrawItemRect(ImColor(255, 0, 0));
            }
            ImGui::Spring(1, 0);
            ImGui::EndVertical();
            ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.x / 2);
        }
        else
            ImGui::Spring(0);
        builder.EndHeader();
    }

    for (auto& input : node.Inputs)
    {
        auto alpha = ImGui::GetStyle().Alpha;
        if (newLinkPin && !graph->CanCreateLink(newLinkPin, &input) && &input != newLinkPin)
            alpha = alpha * (48.0f / 255.0f);

        builder.Input(input.ID);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
        editor->DrawPinIcon(input, graph->IsPinLinked(input.ID), (int)(alpha * 255));
        ImGui::Spring(0);
        if (!input.Name.empty())
        {
            ImGui::TextUnformatted(input.Name.c_str());
            ImGui::Spring(0);
        }
        if (input.Type == PinType::Bool)
        {
            ImGui::Button("Hello");
            ImGui::Spring(0);
        }
        ImGui::PopStyleVar();
        builder.EndInput();
    }

    if (isSimple)
    {
        builder.Middle();

        ImGui::Spring(1, 0);
        ImGui::TextUnformatted(node.Name.c_str());
        ImGui::Spring(1, 0);
    }

    for (auto& output : node.Outputs)
    {
        if (!isSimple && output.Type == PinType::Delegate)
            continue;

        auto alpha = ImGui::GetStyle().Alpha;
        if (newLinkPin && !graph->CanCreateLink(newLinkPin, &output) && &output != newLinkPin)
            alpha = alpha * (48.0f / 255.0f);

        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
        builder.Output(output.ID);
        if (output.Type == PinType::String)
        {
            static char buffer[128] = "Edit Me\nMultiline!";
            static bool wasActive   = false;

            ImGui::PushItemWidth(100.0f);
            ImGui::InputText("##edit", buffer, 127);
            ImGui::PopItemWidth();
            if (ImGui::IsItemActive() && !wasActive)
            {
                ed::EnableShortcuts(false);
                wasActive = true;
            }
            else if (!ImGui::IsItemActive() && wasActive)
            {
                ed::EnableShortcuts(true);
                wasActive = false;
            }
            ImGui::Spring(0);
        }
        if (!output.Name.empty())
        {
            ImGui::Spring(0);
            ImGui::TextUnformatted(output.Name.c_str());
        }
        ImGui::Spring(0);
        editor->DrawPinIcon(output, graph->IsPinLinked(output.ID), (int)(alpha * 255));
        ImGui::PopStyleVar();
        builder.EndOutput();
    }

    builder.End();
}

void EdMetaCodeNode::OnCompile(EdGraphNodeCompileContext const& context) {
}
