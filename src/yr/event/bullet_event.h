#pragma once

#include "yr/yr_event.h"
#include <GeneralStructures.h>
#include <FootClass.h>

class BulletClass;
class BulletTypeClass;
class WarheadTypeClass;
class AbstractClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrBulletCtorEvent
{
public:
    PROPERTY()
    BulletClass* pBullet;
};

CLASS(HookEvent, BindJs)
class YrBulletDtorEvent
{
public:
    PROPERTY()
    BulletClass* pBullet;
};

CLASS(HookEvent, BindJs)
class YrBulletSaveGameBeginEvent
{
public:
    PROPERTY()
    BulletClass* pBullet;
    PROPERTY()
    IStream*     stream;
};

CLASS(HookEvent, BindJs)
class YrBulletSaveGameEndEvent
{
public:
    PROPERTY()
    BulletClass* pBullet;
    PROPERTY()
    IStream*     stream;
};

CLASS(HookEvent, BindJs)
class YrBulletLoadGameBeginEvent
{
public:
    PROPERTY()
    BulletClass* pBullet;
    PROPERTY()
    IStream*     stream;
};

CLASS(HookEvent, BindJs)
class YrBulletLoadGameEndEvent
{
public:
    PROPERTY()
    BulletClass* pBullet;
    PROPERTY()
    IStream*     stream;
};

CLASS(HookEvent, BindJs)
class YrBulletConstructEvent
{
public:
    PROPERTY()
    BulletClass*      pBullet;
    PROPERTY()
    BulletTypeClass*  pBulletType;
    PROPERTY()
    AbstractClass*    pTarget;
    PROPERTY()
    TechnoClass*      pOwner;
    PROPERTY()
    int               damage;
    PROPERTY()
    WarheadTypeClass* pWarhead;
    PROPERTY()
    int               speed;
    PROPERTY()
    bool              bright;
};

CLASS(HookEvent, BindJs)
class YrBulletDetonateEvent
{
public:
    PROPERTY()
    BulletClass*       pBullet;
    PROPERTY()
    CoordStruct const* pCoords;
};

CLASS(HookEvent, BindJs)
class YrBulletSetTargetEvent : public YrHookOverrideReturn<void>
{
public:
    PROPERTY()
    BulletClass* pBullet;
    PROPERTY()
    AbstractClass* pTarget;
};
