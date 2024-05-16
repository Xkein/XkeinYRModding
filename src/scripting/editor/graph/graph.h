#pragma once
#include "node.h"

struct Graph
{

    Node* FindNode(ed::NodeId id);

    Link* FindLink(ed::LinkId id);

    Pin* FindPin(ed::PinId id);

    bool IsPinLinked(ed::PinId id);

    bool CanCreateLink(Pin* a, Pin* b);

    std::vector<Node> nodes;
    std::vector<Link> links;
};