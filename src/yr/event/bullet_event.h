#pragma once

#include "yr/yr_event.h"
#include <GeneralStructures.h>

class BulletClass;
class BulletTypeClass;
class TechnoClass;
class WarheadTypeClass;
class AbstractClass;
struct IStream;

CLASS(HookEvent)
class YrBulletCtorEvent
{
public:
    BulletClass* pBullet;
};

CLASS(HookEvent)
class YrBulletDtorEvent
{
public:
    BulletClass* pBullet;
};

CLASS(HookEvent)
class YrBulletConstructEvent
{
public:
    BulletClass*      pBullet;
    BulletTypeClass*  pBulletType;
    AbstractClass*    pTarget;
    TechnoClass*      pOwner;
    int               damage;
    WarheadTypeClass* pWarhead;
    int               speed;
    bool              bright;
};

CLASS(HookEvent)
class YrBulletDetonateEvent
{
public:
    BulletClass*       pBullet;
    CoordStruct const* pCoords;
};
