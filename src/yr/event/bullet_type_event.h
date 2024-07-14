#pragma once

#include "yr/yr_event.h"

class BulletTypeClass;

CLASS(HookEvent)
class YrBulletTypeCtorEvent
{
public:
    BulletTypeClass* pBulletType {nullptr};
};

CLASS(HookEvent)
class YrBulletTypeDtorEvent
{
public:
    BulletTypeClass* pBulletType {nullptr};
};
