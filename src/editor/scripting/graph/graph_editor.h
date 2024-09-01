#pragma once

#include "ui/imgui/yr_imgui.h"
#include "editor/scripting/graph/graph_node.h"
#include <imgui_node_editor.h>
#include <vector>
#include <map>

namespace ed = ax::NodeEditor;
class EdGraph;
class EdMetaCodeNodeFactory;

struct GraphEditor : YrImGuiWindow
{
    void OnOpen() override;

    void OnFrame() override;

    void OnClose() override;


    int GetNextId();

    // ed::NodeId GetNextNodeId()
    //{
    //     return ed::NodeId(GetNextId());
    // }

    ed::LinkId GetNextLinkId();

    void TouchNode(ed::NodeId id);

    float GetTouchProgress(ed::NodeId id);

    void UpdateTouch();

    // void DrawItemRect(ImColor color, float expand = 0.0f)
    //{
    //     ImGui::GetWindowDrawList()->AddRect(
    //         ImGui::GetItemRectMin() - ImVec2(expand, expand),
    //         ImGui::GetItemRectMax() + ImVec2(expand, expand),
    //         color);
    // };

    // void FillItemRect(ImColor color, float expand = 0.0f, float rounding = 0.0f)
    //{
    //     ImGui::GetWindowDrawList()->AddRectFilled(
    //         ImGui::GetItemRectMin() - ImVec2(expand, expand),
    //         ImGui::GetItemRectMax() + ImVec2(expand, expand),
    //         color, rounding);
    // };

    void BuildNode(EdGraphNode* node);

    void BuildNodes();

    ImColor GetIconColor(EPinType type);

    void DrawPinIcon(const EdGraphPin& pin, bool connected, int alpha);

    void ShowStyleEditor(bool* show = nullptr);

    void ShowLeftPane(float paneWidth);

    std::shared_ptr<EdGraph>               m_graph;
    std::shared_ptr<EdMetaCodeNodeFactory> factory;

    int                                     m_NextId      = 1;
    const int                               m_PinIconSize = 24;
    ImTextureID                             m_HeaderBackground = nullptr;
    ImTextureID                             m_SaveIcon         = nullptr;
    ImTextureID                             m_RestoreIcon      = nullptr;
    const float                             m_TouchTime        = 1.0f;
    std::map<ed::NodeId, float, EdNodeIdLess> m_NodeTouchTime;
    bool                                    m_ShowOrdinals = false;
};
