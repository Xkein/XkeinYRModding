#pragma once
#include "node.h"
#include <memory>

class EdGraph
{
public:
    EdGraphNode* FindNode(ed::NodeId id);

    EdGraphLink* FindLink(ed::LinkId id);

    EdGraphPin* FindPin(ed::PinId id);

    bool IsPinLinked(ed::PinId id);

    bool CanCreateLink(EdGraphPin* a, EdGraphPin* b);

    void AddLink(EdGraphLink link);
    void RemoveLink(ed::LinkId id);
    void RemoveLink(const EdGraphLink &link);
    
    void AddNode(std::shared_ptr<EdGraphNode> node);
    void RemoveNode(ed::NodeId id);
    void RemoveNode(EdGraphNode* node);
    
    std::vector<std::shared_ptr<EdGraphNode>> nodes;
    std::vector<EdGraphLink> links;
};