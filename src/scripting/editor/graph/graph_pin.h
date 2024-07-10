#pragma once

#include <imgui_node_editor.h>
#include "core/reflection/reflection.h"
#include <string>
#include "scripting/editor/blueprints/utilities/builders.h"

namespace ed = ax::NodeEditor;

enum class EPinType
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

struct EdGraphNode;

struct EdGraphPinType
{
    entt::meta_type type;
    entt::meta_any  defaultValue;
};

struct EdGraphPin
{
    ed::PinId       ID;
    EdGraphNode*    Node;
    std::string     Name;
    EPinType        Type;
    PinKind         Kind;
    EdGraphNode*    LinkedTo {nullptr};

    EdGraphPinType PinType;

    EdGraphPin(int id, const char* name, EPinType type) : ID(id), Node(nullptr), Name(name), Type(type), Kind(PinKind::Input) {}
};
