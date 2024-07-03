#include "node_factory.h"

EdMetaCodeNodeFactory::EdMetaCodeNodeFactory()
{
    CollectAllMeta();
}

void EdMetaCodeNodeFactory::CollectAllMeta()
{
    metaList.clear();

    for (auto&& [id, type] : entt::resolve())
    {
        EdMetaCodeNodeMeta* meta = new EdMetaCodeNodeMeta();
        meta->type = type;
        AddNodeMeta(std::unique_ptr<EdGraphNodeMeta>{meta});
    }
}

void EdMetaCodeNodeFactory::AddNodeMeta(std::unique_ptr<EdGraphNodeMeta> meta)
{
    metaList.emplace_back(std::move(meta));
}

void EdMetaCodeNodeFactory::RemoveNodeMeta(EdGraphNodeMeta* meta)
{
    auto iter = std::find_if(metaList.begin(), metaList.end(), [meta](auto& ptr) {
        return ptr->id == meta->id;
    });
    if (iter == metaList.end())
        return;
    metaList.erase(iter);
}

std::shared_ptr<EdGraphNode> EdMetaCodeNodeFactory::CreateNode(EdGraphNodeCreateInfo const& info)
{
    EdMetaCodeNode* node = new EdMetaCodeNode(info.getNextId(), info.name);

    node->Inputs.emplace_back(info.getNextId(), "", PinType::Flow);
    node->Inputs.emplace_back(info.getNextId(), "In String", PinType::String);
    node->Outputs.emplace_back(info.getNextId(), "", PinType::Flow);

    return std::shared_ptr<EdGraphNode>(node);
}
