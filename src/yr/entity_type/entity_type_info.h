#pragma once

#include "core/object.h"
#include "yr/entity.h"
#include "yr/read_scheduler.h"

#include <memory>
#include <vector>
#include <functional>

#define IMPLEMENT_ENTITY_TYPE_INFO(TEntityTypeInfo, TYrEntityType) \
    template<> \
    template<> \
    int EntityTypeInfoMeta<TEntityTypeInfo>::GetIndex_Impl<TYrEntityType>() \
    { \
        static int index = EntityTypeInfoMap<TYrEntityType>::SetNextIndex([](YrEntity yrEntity) { return std::make_shared<TEntityTypeInfo>(yrEntity); }); \
        return index; \
    }

class EntityTypeInfo : public Object, public IReadTask
{
protected:
    EntityTypeInfo(YrEntity yrEntity);

public:
    virtual const char* GetName();

    virtual void Read(Ini& ini) override final;

    virtual void Read(Ini& ini, IniSection& section);

    virtual void ReadCustom() override;

private:
    YrEntity yrEntity;

};

class IEntityTypeInfoMap
{
public:
    virtual ~IEntityTypeInfoMap() {}

    virtual int GetCount() = 0;

    virtual std::weak_ptr<EntityTypeInfo> GetInfo(int index) = 0;
};

template<class TYrEntityType>
class EntityTypeInfoMap : public IEntityTypeInfoMap
{
    // static_assert(!std::is_final_v<TYrEntityType>, "EntityTypeInfoMap is valid only on top YrEntityType!");

private:
    static int infoCount;

    static std::vector<std::function<std::shared_ptr<EntityTypeInfo>(YrEntity)>> infoCreator;

public:
    static int SetNextIndex(std::function<std::shared_ptr<EntityTypeInfo>(YrEntity)> creator)
    {
        infoCreator.push_back(std::move(creator));
        return infoCount++;
    }
    static int GetInfoCount()
    {
        return infoCount;
    }

    EntityTypeInfoMap(YrEntity yrEntity)
    {
        entityTypeInfoList.resize(infoCount);
        entityTypeInfoList.reserve(infoCount);

        for (int idx = 0; idx < infoCount; idx++)
        {
            entityTypeInfoList[idx] = infoCreator[idx](yrEntity);
        }
    }

    virtual ~EntityTypeInfoMap() {}

    virtual int GetCount() override {
        return GetInfoCount();
    }

    virtual std::weak_ptr<EntityTypeInfo> GetInfo(int index) override {
        return entityTypeInfoList[index];
    }

    template<class TEntityTypeInfo>
    std::weak_ptr<TEntityTypeInfo> GetEntityTypeInfo();

private:
    std::vector<std::shared_ptr<EntityTypeInfo>> entityTypeInfoList;

};

template<class TYrEntityType>
int EntityTypeInfoMap<TYrEntityType>::infoCount = 0;

template<class TYrEntityType>
std::vector<std::function<std::shared_ptr<EntityTypeInfo>(YrEntity)>> EntityTypeInfoMap<TYrEntityType>::infoCreator;

template<class TEntityTypeInfo>
class EntityTypeInfoMeta
{
public:
    template<class TYrEntityType>
    static int GetIndex()
    {
        return GetIndex_Impl<TYrEntityType>();
    }

private:
    template<class TYrEntityType>
    static int GetIndex_Impl();
};


template<class TYrEntityType>
template<class TEntityTypeInfo>
std::weak_ptr<TEntityTypeInfo> EntityTypeInfoMap<TYrEntityType>::GetEntityTypeInfo()
{
    using Meta = EntityTypeInfoMeta<TEntityTypeInfo>;

    const int index = Meta().GetIndex<TYrEntityType>();

    return std::reinterpret_pointer_cast<TEntityTypeInfo>(entityTypeInfoList[index]);
}
