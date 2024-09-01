#include "graph.h"


 EdGraphNode* EdGraph::FindNode(ed::NodeId id)
{
    for (auto& node : nodes)
        if (node->ID == id)
            return node.get();

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
        for (auto& pin : node->Inputs)
            if (pin.ID == id)
                return &pin;

        for (auto& pin : node->Outputs)
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
    if (a->Type == EPinType::Object)
    {
        return a->PinType.type == b->PinType.type;
    }

    return true;
}

void EdGraph::AddLink(EdGraphLink link)
{
    links.push_back(std::move(link));
}

void EdGraph::RemoveLink(ed::LinkId id)
{
    auto iter = std::find_if(links.begin(), links.end(), [id](auto& link) {
        return link.ID == id;
    });
    if (iter != links.end())
        links.erase(iter);
}

void EdGraph::RemoveLink(const EdGraphLink& link)
{
    RemoveLink(link.ID);
}

void EdGraph::AddNode(std::shared_ptr<EdGraphNode> node)
{
    nodes.emplace_back(std::move(node));
}

void EdGraph::RemoveNode(ed::NodeId id)
{
    auto iter = std::find_if(nodes.begin(), nodes.end(), [id](auto& link) {
        return link->ID == id;
    });
    if (iter != nodes.end())
        nodes.erase(iter);
}

void EdGraph::RemoveNode(EdGraphNode* node)
{
    RemoveNode(node->ID);
}
