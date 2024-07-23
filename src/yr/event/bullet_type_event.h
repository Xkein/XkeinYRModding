#pragma once

#include "yr/yr_event.h"

class BulletTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrBulletTypeCtorEvent
{
public:
    BulletTypeClass* pBulletType;
};

CLASS(HookEvent)
class YrBulletTypeDtorEvent
{
public:
    BulletTypeClass* pBulletType;
};

CLASS(HookEvent)
class YrBulletTypeLoadIniEvent
{
public:
    BulletTypeClass* pBulletType;
    CCINIClass*      pIni;
};
