#pragma once
#include "node.h"

struct EdGraph
{

    EdGraphNode* FindNode(ed::NodeId id);

    EdGraphLink* FindLink(ed::LinkId id);

    EdGraphPin* FindPin(ed::PinId id);

    bool IsPinLinked(ed::PinId id);

    bool CanCreateLink(EdGraphPin* a, EdGraphPin* b);

    std::vector<EdGraphNode> nodes;
    std::vector<EdGraphLink> links;
};