#pragma once

#include "yr/yr_event.h"

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
    BulletClass* pBullet {nullptr};
};

CLASS(HookEvent)
class YrBulletDtorEvent
{
public:
    BulletClass* pBullet {nullptr};
};

CLASS(HookEvent)
class YrBulletConstructEvent
{
public:
    BulletClass*      pBullet {nullptr};
    BulletTypeClass*  pBulletType {nullptr};
    AbstractClass*    pTarget {nullptr};
    TechnoClass*      pOwner {nullptr};
    int               damage {0};
    WarheadTypeClass* pWarhead {nullptr};
    int               speed {0};
    bool              bright {false};
};
