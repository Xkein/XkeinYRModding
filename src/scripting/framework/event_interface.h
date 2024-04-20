#pragma once

struct IEventInterfaceBase
{};

struct ITickable : public virtual IEventInterfaceBase
{
    virtual void Tick(float deltaTime) = 0;
};

struct IBeginEndTickable : public virtual IEventInterfaceBase
{
    virtual void BeginTick(float deltaTime) = 0;
    virtual void EndTick(float deltaTime)   = 0;
};

struct ICreateDestroy : public virtual IEventInterfaceBase
{
    virtual void OnCreate()  = 0;
    virtual void OnDestroy() = 0;
};

template<class T>
concept ConceptTickable = requires(T obj, float deltaTime) { obj.Tick(deltaTime); };
