#pragma once

#include <imgui_node_editor.h>
#include <imgui_internal.h>

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

#include "scripting/editor/blueprints/utilities/builders.h"

namespace ed   = ax::NodeEditor;
class GraphEditor;
struct EdGraphPin;

struct EdGraphNodeDrawContext
{
    GraphEditor*                         editor;
    ed::Utilities::BlueprintNodeBuilder* builder;
    EdGraphPin*                          newLinkPin;
};

struct EdGraphNodeCompileContext
{

};

enum class PinType
{
    Flow,
    Bool,
    Int,
    Float,
    String,
    Object,
    Function,
    Delegate,
};

enum class PinKind
{
    Output,
    Input
};

enum class NodeType
{
    Blueprint,
    Simple,
    Tree,
    Comment,
    Houdini
};

struct EdGraphNode;

struct EdGraphPin
{
    ed::PinId    ID;
    EdGraphNode* Node;
    std::string  Name;
    PinType      Type;
    PinKind      Kind;
    EdGraphNode* LinkedTo {nullptr};

    EdGraphPin(int id, const char* name, PinType type) : ID(id), Node(nullptr), Name(name), Type(type), Kind(PinKind::Input) {}
};

class EdGraphNode
{
public:
    ed::NodeId       ID;
    std::string      Name;
    std::vector<EdGraphPin> Inputs;
    std::vector<EdGraphPin> Outputs;
    ImColor          Color;
    NodeType         Type;
    ImVec2           Size;

    std::string State;
    std::string SavedState;

    EdGraphNode(int id, const char* name, ImColor color = ImColor(255, 255, 255)) : ID(id), Name(name), Color(color), Type(NodeType::Blueprint), Size(0, 0) {}

    virtual void OnDraw(EdGraphNodeDrawContext const& context) = 0;
    virtual void OnBeforeCompile(EdGraphNodeCompileContext const& context) {}
    virtual void OnCompile(EdGraphNodeCompileContext const& context) = 0;
};

struct EdGraphLink
{
    ed::LinkId ID;

    ed::PinId StartPinID;
    ed::PinId EndPinID;

    ImColor Color;

    EdGraphLink(ed::LinkId id, ed::PinId startPinId, ed::PinId endPinId, ImColor color = ImColor(255, 255, 255)) : ID(id), StartPinID(startPinId), EndPinID(endPinId), Color(color) {}
};

struct EdNodeIdLess
{
    bool operator()(const ed::NodeId& lhs, const ed::NodeId& rhs) const
    {
        return lhs.AsPointer() < rhs.AsPointer();
    }
};

struct EdCommentNode : public EdGraphNode {

};

struct EdMetaCodeNode : public EdGraphNode
{
    EdMetaCodeNode(int id, const char* name, ImColor color = ImColor(255, 255, 255)) : EdGraphNode(id, name, color) {}

    void OnDraw(EdGraphNodeDrawContext const& context) override;
    void OnCompile(EdGraphNodeCompileContext const& context) override;
};

