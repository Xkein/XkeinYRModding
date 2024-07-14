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

BROADCAST_HOOK_EVENT(0x46BDD9, 0x5, YrBulletTypeCtorEvent)
{
    E->pBulletType = R->EAX<BulletTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x46C8B6, 0x6, YrBulletTypeDtorEvent)
{
    E->pBulletType = R->ESI<BulletTypeClass*>();
}
