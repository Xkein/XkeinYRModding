#pragma once
#include "scripting/editor/graph/node.h"
#include "core/reflection/reflection.h"
#include <memory>
#include <functional>

struct EdGraphNodeMeta {
    std::string id;
    const char* category;
    std::string name;
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
};

struct EdMetaCodeNodeMeta : public EdGraphNodeMeta
{
    bool IsFunction() const
    {
        return static_cast<bool>(func);
    }
    bool IsField() const
    {
        return static_cast<bool>(data);
    }
    bool IsSetter() const
    {
        return IsField() && isSetter;
    }
    bool IsGetter() const
    {
        return IsField() && !isSetter;
    }

    entt::meta_type klass;
    entt::meta_func func;
    entt::meta_data data;
    bool            isSetter;
};

class EdMetaCodeNodeFactory : public EdNodeFactory
{
public:
    EdMetaCodeNodeFactory();
    void CollectAllMeta();

    void AddNodeMeta(std::unique_ptr<EdGraphNodeMeta> meta) override;
    void RemoveNodeMeta(EdGraphNodeMeta* meta) override;

    std::shared_ptr<EdGraphNode> CreateNode(EdGraphNodeCreateInfo const& info) override;

    std::vector<std::unique_ptr<EdGraphNodeMeta>>        metaList;
    std::map<std::string, std::vector<EdGraphNodeMeta*>> metaListByCategory;
};
