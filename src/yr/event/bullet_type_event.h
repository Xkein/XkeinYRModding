#pragma once

#include "yr/yr_event.h"

class BulletTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrBulletTypeCtorEvent
{
public:
    PROPERTY()
    BulletTypeClass* pBulletType;
};

CLASS(HookEvent, BindJs)
class YrBulletTypeDtorEvent
{
public:
    PROPERTY()
    BulletTypeClass* pBulletType;
};

CLASS(HookEvent, BindJs)
class YrBulletTypeSaveGameBeginEvent
{
public:
    PROPERTY()
    BulletTypeClass* pBulletType;
    PROPERTY()
    IStream*         stream;
};

CLASS(HookEvent, BindJs)
class YrBulletTypeSaveGameEndEvent
{
public:
    PROPERTY()
    BulletTypeClass* pBulletType;
    PROPERTY()
    IStream*         stream;
};

CLASS(HookEvent, BindJs)
class YrBulletTypeLoadGameBeginEvent
{
public:
    PROPERTY()
    BulletTypeClass* pBulletType;
    PROPERTY()
    IStream*         stream;
};

CLASS(HookEvent, BindJs)
class YrBulletTypeLoadGameEndEvent
{
public:
    PROPERTY()
    BulletTypeClass* pBulletType;
    PROPERTY()
    IStream*         stream;
};

CLASS(HookEvent, BindJs)
class YrBulletTypeLoadIniEvent
{
public:
    PROPERTY()
    BulletTypeClass* pBulletType;
    PROPERTY()
    CCINIClass*      pIni;
};
