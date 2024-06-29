#include "graph.h"


 EdGraphNode* EdGraph::FindNode(ed::NodeId id)
{
    for (auto& node : nodes)
        if (node.ID == id)
            return &node;

    return nullptr;
}
EdGraphLink* EdGraph::FindLink(ed::LinkId id)
{
    for (auto& link : links)
        if (link.ID == id)
            return &link;

    return nullptr;
}
EdGraphPin* EdGraph::FindPin(ed::PinId id)
{
    if (!id)
        return nullptr;

    for (auto& node : nodes)
    {
        for (auto& pin : node.Inputs)
            if (pin.ID == id)
                return &pin;

        for (auto& pin : node.Outputs)
            if (pin.ID == id)
                return &pin;
    }

    return nullptr;
}
bool EdGraph::IsPinLinked(ed::PinId id)
{
    if (!id)
        return false;

    for (auto& link : links)
        if (link.StartPinID == id || link.EndPinID == id)
            return true;

    return false;
}
bool EdGraph::CanCreateLink(EdGraphPin* a, EdGraphPin* b)
{
    if (!a || !b || a == b || a->Kind == b->Kind || a->Type != b->Type || a->Node == b->Node)
        return false;

    return true;
}
