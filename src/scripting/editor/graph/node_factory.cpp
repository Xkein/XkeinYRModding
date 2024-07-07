#include "node_factory.h"
#include <format>
using namespace entt::literals;

EdMetaCodeNodeFactory::EdMetaCodeNodeFactory()
{
    CollectAllMeta();
}

void EdMetaCodeNodeFactory::CollectAllMeta()
{
    metaList.clear();

    auto AddClass = [this](entt::meta_type type) {
        const char* catagory = type.prop("name"_hs).value().cast<const char*>();
        for (auto&& [id, func] : type.func())
        {
            EdMetaCodeNodeMeta* meta = new EdMetaCodeNodeMeta();
            meta->klass              = type;
            meta->category           = catagory;
            meta->name               = func.prop("name"_hs).value().cast<const char*>();
            meta->func               = func;
            
            AddNodeMeta(std::unique_ptr<EdGraphNodeMeta> {meta});
        }
        for (auto&& [id, data] : type.data())
        {
            EdMetaCodeNodeMeta* getterMeta = new EdMetaCodeNodeMeta();
            getterMeta->klass              = type;
            getterMeta->category           = catagory;
            getterMeta->name               = std::string("Get ") + data.prop("name"_hs).value().cast<const char*>();
            getterMeta->data               = data;
            getterMeta->isSetter           = false;

            AddNodeMeta(std::unique_ptr<EdGraphNodeMeta> {getterMeta});

            EdMetaCodeNodeMeta* setterMeta = new EdMetaCodeNodeMeta();
            setterMeta->klass              = type;
            setterMeta->category           = catagory;
            setterMeta->name               = std::string("Set ") + data.prop("name"_hs).value().cast<const char*>();
            setterMeta->data               = data;
            setterMeta->isSetter           = true;

            AddNodeMeta(std::unique_ptr<EdGraphNodeMeta> {setterMeta});
        }
    };
    for (auto&& [id, type] : entt::resolve())
    {
        AddClass(type);
    }

    // TODO: Add Event
}

void EdMetaCodeNodeFactory::AddNodeMeta(std::unique_ptr<EdGraphNodeMeta> meta)
{
    auto& categoryMetaList = metaListByCategory[meta->category];
    categoryMetaList.push_back(meta.get());
    metaList.emplace_back(std::move(meta));
}

void EdMetaCodeNodeFactory::RemoveNodeMeta(EdGraphNodeMeta* meta)
{
    auto iter = std::find_if(metaList.begin(), metaList.end(), [meta](auto& ptr) {
        return ptr->id == meta->id;
    });
    if (iter == metaList.end())
        return;
    auto& categoryMetaList = metaListByCategory[meta->category];
    categoryMetaList.erase(std::find(categoryMetaList.begin(), categoryMetaList.end(), meta));
    metaList.erase(iter);
}

PinType GetPinType(entt::meta_type type) {
    if (type.is_class())
    {
        return PinType::Object;
    }
    else if (type.is_integral())
    {
        return PinType::Int;
    }
    else if (type.is_arithmetic())
    {
        return PinType::Float;
    }
    else
    {
        // not valid
        return PinType::Object;
    }
}

std::shared_ptr<EdGraphNode> EdMetaCodeNodeFactory::CreateNode(EdGraphNodeCreateInfo const& info)
{
    EdMetaCodeNode* node = new EdMetaCodeNode(info.getNextId(), info.name);
    EdMetaCodeNodeMeta const* meta = static_cast<EdMetaCodeNodeMeta const*>(info.meta);

    entt::meta_type klass    = meta->klass;
    const char*     className = klass.prop("name"_hs).value().cast<const char*>();
    if (meta->IsFunction())
    {
        node->Inputs.emplace_back(info.getNextId(), "", PinType::Flow);
        entt::meta_func func = meta->func;
        bool            isStatic = func.is_static();
        if (!isStatic)
        {
            node->Inputs.emplace_back(info.getNextId(), className, GetPinType(klass));
        }
        size_t argCount = func.arity();
        for (size_t idx = 0; idx < argCount; idx++)
        {
            entt::meta_type arg = func.arg(idx);
            node->Inputs.emplace_back(info.getNextId(), func.prop(entt::hashed_string{std::format("arg{}", idx).c_str()}).value().cast<const char*>(), GetPinType(arg));
        }

        node->Outputs.emplace_back(info.getNextId(), "", PinType::Flow);
        entt::meta_type ret = func.ret();
        if (ret)
        {
            node->Outputs.emplace_back(info.getNextId(), "Value", GetPinType(ret));
        }
    }
    else if (meta->IsField())
    {
        entt::meta_data data     = meta->data;
        bool            isSetter = meta->IsSetter();
        if (isSetter)
        {
            node->Inputs.emplace_back(info.getNextId(), "", PinType::Flow);
            node->Outputs.emplace_back(info.getNextId(), "", PinType::Flow);
        }
        node->Inputs.emplace_back(info.getNextId(), className, GetPinType(klass));
        if (isSetter)
        {
            node->Inputs.emplace_back(info.getNextId(), "Value", GetPinType(data.type()));
        }
        node->Outputs.emplace_back(info.getNextId(), "Value", GetPinType(data.type()));
    }

    return std::shared_ptr<EdGraphNode>(node);
}
