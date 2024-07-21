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
BROADCAST_HOOK_EVENT(0x466556, 0x6, YrBulletConstructEvent)
{
    E->pBullet = R->ESI<BulletClass*>();
    E->pBulletType = R->Stack<BulletTypeClass*>(STACK_OFFSET(0x4, 0x4));
    E->pTarget = R->Stack<AbstractClass*>(STACK_OFFSET(0x4, 0x8));
    E->pOwner = R->Stack<TechnoClass*>(STACK_OFFSET(0x4, 0xC));
    E->damage = R->Stack<int>(STACK_OFFSET(0x4, 0x10));
    E->pWarhead = R->Stack<WarheadTypeClass*>(STACK_OFFSET(0x4, 0x14));
    E->speed = R->Stack<int>(STACK_OFFSET(0x4, 0x18));
    E->bright = R->Stack<bool>(STACK_OFFSET(0x4, 0x1C));
}

BROADCAST_HOOK_EVENT(0x46BDD9, 0x5, YrBulletTypeCtorEvent)
{
    E->pBulletType = R->EAX<BulletTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x46C8B6, 0x6, YrBulletTypeDtorEvent)
{
    E->pBulletType = R->ESI<BulletTypeClass*>();
}
