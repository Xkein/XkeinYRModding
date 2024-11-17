#include "render/backend/render_backend.h"
#include "physics/yr_tools.h"
#include "runtime/logger/logger.h"
#include "yr/api/yr_entity.h"
#include "yr/extcore_config.h"

#include <AircraftClass.h>
#include <AnimClass.h>
#include <BuildingClass.h>
#include <BuildingLightClass.h>
#include <BulletClass.h>
#include <InfantryClass.h>
#include <IsometricTileClass.h>
#include <OverlayClass.h>
#include <ParticleClass.h>
#include <ParticleSystemClass.h>
#include <SmudgeClass.h>
#include <TerrainClass.h>
#include <UnitClass.h>
#include <VeinholeMonsterClass.h>
#include <VoxelAnimClass.h>
#include <WaveClass.h>

#include <msgpack.hpp>
#include <vector>
#include <zmq.hpp>

struct RenderSyncComponent
{
    int            id;
    AbstractClass* owner;
    JPH::Vec3      lastPosition;
    JPH::Quat      lastQuat;
};

struct RenderSyncTransformPack
{
    int id;

    float posx;
    float posy;
    float posz;

    float rotx;
    float roty;
    float rotz;
    float rotw;
    
    MSGPACK_DEFINE(id, posx, posy, posz, rotx, roty, rotz, rotw);
};

struct RenderSyncFramePack
{
    std::vector<int>                     newObjects;
    std::vector<int>                     removedObjects;
    std::vector<RenderSyncTransformPack> transforms;
    
    MSGPACK_DEFINE(newObjects, removedObjects, transforms);

    bool IsEmpty() const
    {
        return newObjects.empty() && removedObjects.empty() && transforms.empty();
    }

    void Clear()
    {
        newObjects.clear();
        removedObjects.clear();
        transforms.clear();
    }
};

class RenderBackendImpl
{
public:
    RenderBackendImpl() {}

    ~RenderBackendImpl()
    {
        StopServer();
    }

    void StartServer()
    {
        int port = gYrExtConfig->rawData.value("render_server_port", 9900);

        zmq::context_t context {-1};
        socket = zmq::socket_t(context, ZMQ_PAIR);

        socket.bind(std::format("tcp://*:{}", port));

        curId = 0;
        BindObjects();
    }

    void StopServer()
    {
        UnbindObjects();
        socket.close();
    }

    void BindObjects()
    {
        BindYrObject<AnimClass>();
        BindYrObject<VoxelAnimClass>();
        BindYrObject<BuildingClass>();
        BindYrObject<AircraftClass>();
        BindYrObject<InfantryClass>();
        BindYrObject<UnitClass>();
        BindYrObject<BulletClass>();
        BindYrObject<TerrainClass>();
        BindYrObject<BuildingLightClass>();
        BindYrObject<WaveClass>();
        BindYrObject<ParticleClass>();
        BindYrObject<ParticleSystemClass>();
        BindYrObject<IsometricTileClass>();
        BindYrObject<OverlayClass>();
        BindYrObject<SmudgeClass>();
        BindYrObject<VeinholeMonsterClass>();
    }

    void UnbindObjects()
    {
        UnbindYrObject<AnimClass>();
        UnbindYrObject<VoxelAnimClass>();
        UnbindYrObject<BuildingClass>();
        UnbindYrObject<AircraftClass>();
        UnbindYrObject<InfantryClass>();
        UnbindYrObject<UnitClass>();
        UnbindYrObject<BulletClass>();
        UnbindYrObject<TerrainClass>();
        UnbindYrObject<BuildingLightClass>();
        UnbindYrObject<WaveClass>();
        UnbindYrObject<ParticleClass>();
        UnbindYrObject<ParticleSystemClass>();
        UnbindYrObject<IsometricTileClass>();
        UnbindYrObject<OverlayClass>();
        UnbindYrObject<SmudgeClass>();
        UnbindYrObject<VeinholeMonsterClass>();
    }

    template<typename Type>
    void BindYrObject()
    {
        for (auto&& [entity, com] : gEntt->view<YrEntityComponent<Type>>().each())
        {
            CreateComponent<Type>(this, *gEntt, entity);
        }

        gEntt->on_construct<YrEntityComponent<Type>>().template connect<&CreateComponent<Type>>(this);
        gEntt->on_destroy<YrEntityComponent<Type>>().template connect<&DestroyComponent>(this);
    }

    template<typename Type>
    void UnbindYrObject()
    {
        for (auto&& [entity, com] : gEntt->view<YrEntityComponent<Type>>().each())
        {
            gEntt->remove<RenderSyncComponent>(entity);
        }

        gEntt->on_construct<YrEntityComponent<Type>>().template disconnect<&CreateComponent<Type>>(this);
        gEntt->on_destroy<YrEntityComponent<Type>>().template disconnect<&DestroyComponent>(this);
    }

    template<typename Type>
    static void CreateComponent(RenderBackendImpl* backend, entt::registry& reg, entt::entity entity)
    {
        Type*                pYrObject = reg.get<YrEntityComponent<Type>>(entity).yrObject;
        RenderSyncComponent& com       = reg.emplace<RenderSyncComponent>(entity);
        com.owner                      = pYrObject;
        com.id                         = ++backend->curId;

        backend->framePack.newObjects.push_back(com.id);
    }

    static void DestroyComponent(RenderBackendImpl* backend, entt::registry& reg, entt::entity entity)
    {
        RenderSyncComponent& com = reg.get<RenderSyncComponent>(entity);

        backend->framePack.removedObjects.push_back(com.id);
    }

    void Tick()
    {
        

        for (auto&& [entity, com] : gEntt->view<RenderSyncComponent>().each())
        {
            AbstractClass* pYrObject = com.owner;
            JPH::Vec3      position  = ToVec3(GetObjectCoords(pYrObject));
            JPH::Quat      quat      = ToQuat(GetObjectRotation(pYrObject));
            if (quat.IsNaN())
            {
                quat = JPH::Quat::sIdentity();
                gLogger->error("{} rotation is NaN!", (void*)pYrObject);
            }
            else
            {
                quat = quat.Normalized();
            }
            if (com.lastPosition == position || com.lastQuat == quat)
                continue;

            RenderSyncTransformPack pack;
            pack.id = com.id;

            pack.posx = position.GetX();
            pack.posy = position.GetY();
            pack.posz = position.GetZ();

            pack.rotx = quat.GetX();
            pack.roty = quat.GetY();
            pack.rotz = quat.GetZ();
            pack.rotw = quat.GetW();

            framePack.transforms.push_back(pack);
        }

        if (framePack.IsEmpty())
            return;

        // msgpack::
        // socket.send()

        framePack.Clear();
    }

    zmq::socket_t socket;

    RenderSyncFramePack framePack;
    int                 curId;
};

RenderBackend::RenderBackend()
{
    _impl = new RenderBackendImpl();
}

RenderBackend::~RenderBackend()
{
    delete _impl;
}

void RenderBackend::StartServer()
{
    _impl->StartServer();
}

void RenderBackend::Tick()
{
    _impl->Tick();
}

#include "yr/yr_all_events.h"
