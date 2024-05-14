#include "graph.h"


 Node* Graph::FindNode(ed::NodeId id)
{
    for (auto& node : nodes)
        if (node.ID == id)
            return &node;

    return nullptr;
}
Link* Graph::FindLink(ed::LinkId id)
{
    for (auto& link : links)
        if (link.ID == id)
            return &link;

    return nullptr;
}
Pin* Graph::FindPin(ed::PinId id)
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
bool Graph::IsPinLinked(ed::PinId id)
{
    if (!id)
        return false;

    for (auto& link : links)
        if (link.StartPinID == id || link.EndPinID == id)
            return true;

    return false;
}
bool Graph::CanCreateLink(Pin* a, Pin* b)
{
    if (!a || !b || a == b || a->Kind == b->Kind || a->Type != b->Type || a->Node == b->Node)
        return false;

    return true;
}
