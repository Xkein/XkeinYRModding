#pragma once

#include "yr/yr_event.h"

class BulletClass;
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
