#pragma once
#include "scripting/editor/graph/node.h"
#include "core/reflection/reflection.h"
#include <memory>
#include <functional>

struct EdGraphNodeMeta {
    std::string id;
};

struct EdGraphNodeCreateInfo
{
    EdGraphNodeMeta const* meta;
    const char*            name;
    std::function<int()>   getNextId;
};

class EdNodeFactory
{
public:
    virtual void AddNodeMeta(std::unique_ptr<EdGraphNodeMeta> meta) = 0;
    virtual void RemoveNodeMeta(EdGraphNodeMeta* meta)              = 0;

    virtual std::shared_ptr<EdGraphNode> CreateNode(EdGraphNodeCreateInfo const& info) = 0;

    std::vector<std::unique_ptr<EdGraphNodeMeta>> metaList;
};

struct EdMetaCodeNodeMeta : public EdGraphNodeMeta
{
    entt::meta_type type;
};

class EdMetaCodeNodeFactory : public EdNodeFactory
{
public:
    EdMetaCodeNodeFactory();
    void CollectAllMeta();

    void AddNodeMeta(std::unique_ptr<EdGraphNodeMeta> meta) override;
    void RemoveNodeMeta(EdGraphNodeMeta* meta) override;

    std::shared_ptr<EdGraphNode> CreateNode(EdGraphNodeCreateInfo const& info) override;
};
