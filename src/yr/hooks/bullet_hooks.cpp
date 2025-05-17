#include "yr/event/bullet_event.h"
#include "yr/event/bullet_type_event.h"
#include "yr/yr_hook.h"

#include <BulletClass.h>
#include <BulletTypeClass.h>
#include <FootClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT(0x4664BA, 0x5, YrBulletCtorEvent)
{
    E->pBullet = R->ESI<BulletClass*>();
}
BROADCAST_HOOK_EVENT(0x4665E9, 0xA, YrBulletDtorEvent)
{
    E->pBullet = R->ESI<BulletClass*>();
}
BROADCAST_HOOK_EVENT(0x46AFB0, 0x8, YrBulletSaveGameBeginEvent)
{
    E->pBullet = R->Stack<BulletClass*>(0x4);
    E->stream  = R->Stack<IStream*>(0x8);

    gSavingObject = E->pBullet;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x46AFC4, 0x5, YrBulletSaveGameEndEvent)
{
    E->pBullet = reinterpret_cast<BulletClass*>(gSavingObject);
    E->stream  = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x46AE70, 0x5, YrBulletLoadGameBeginEvent)
{
    E->pBullet = R->Stack<BulletClass*>(0x4);
    E->stream  = R->Stack<IStream*>(0x8);

    gSavingObject = E->pBullet;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT_AGAIN(0x46AF97, 0x7, YrBulletLoadGameEndEvent, 0x46AF9E)
BROADCAST_HOOK_EVENT(0x46AF9E, 0x7, YrBulletLoadGameEndEvent)
{
    E->pBullet = reinterpret_cast<BulletClass*>(gSavingObject);
    E->stream  = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x466556, 0x6, YrBulletConstructEvent)
{
    E->pBullet     = R->ECX<BulletClass*>();
    E->pBulletType = R->Stack<BulletTypeClass*>(STACK_OFFSET(0x4, 0x4));
    E->pTarget     = R->Stack<AbstractClass*>(STACK_OFFSET(0x4, 0x8));
    E->pOwner      = R->Stack<TechnoClass*>(STACK_OFFSET(0x4, 0xC));
    E->damage      = R->Stack<int>(STACK_OFFSET(0x4, 0x10));
    E->pWarhead    = R->Stack<WarheadTypeClass*>(STACK_OFFSET(0x4, 0x14));
    E->speed       = R->Stack<int>(STACK_OFFSET(0x4, 0x18));
    E->bright      = R->Stack<bool>(STACK_OFFSET(0x4, 0x1C));
}
BROADCAST_HOOK_EVENT(0x4690B0, 0x6, YrBulletDetonateEvent)
{
    E->pBullet = R->ECX<BulletClass*>();
    E->pCoords = R->Stack<CoordStruct const*>(0x4);
}

BROADCAST_HOOK_EVENT(0x46BDD9, 0x5, YrBulletTypeCtorEvent)
{
    E->pBulletType = R->EAX<BulletTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x46C8B6, 0x6, YrBulletTypeDtorEvent)
{
    E->pBulletType = R->ESI<BulletTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x46C730, 0x8, YrBulletTypeSaveGameBeginEvent)
{
    E->pBulletType = R->Stack<BulletTypeClass*>(0x4);
    E->stream      = R->Stack<IStream*>(0x8);

    gSavingObject = E->pBulletType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x46C74A, 0x5, YrBulletTypeSaveGameEndEvent)
{
    E->pBulletType = reinterpret_cast<BulletTypeClass*>(gSavingObject);
    E->stream      = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x46C6A0, 0x5, YrBulletTypeLoadGameBeginEvent)
{
    E->pBulletType = R->Stack<BulletTypeClass*>(0x4);
    E->stream      = R->Stack<IStream*>(0x8);

    gSavingObject = E->pBulletType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x46C722, 0x5, YrBulletTypeLoadGameEndEvent)
{
    E->pBulletType = reinterpret_cast<BulletTypeClass*>(gSavingObject);
    E->stream      = gSavingStream;
}

BROADCAST_HOOK_EVENT_AGAIN(0x46C429, 0xA, YrBulletTypeLoadIniEvent, 0x46C41C)
BROADCAST_HOOK_EVENT(0x46C41C, 0xA, YrBulletTypeLoadIniEvent)
{
    E->pBulletType = R->ESI<BulletTypeClass*>();
    E->pIni        = R->Stack<CCINIClass*>(0x90);
}
