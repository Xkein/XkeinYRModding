#include "entity_type_info.h"
#include "resources/ini.h"

#include <AbstractTypeClass.h>

EntityTypeInfo::EntityTypeInfo(YrEntity yrEntity) : Object(), yrEntity(yrEntity)
{
}

const char* EntityTypeInfo::GetName()
{
    return yrEntity.yrTypeObject->Name;
}

void EntityTypeInfo::Read(Ini& ini)
{
    Read(ini, ini.GetSection(yrEntity.yrTypeObject->ID));
}

void EntityTypeInfo::Read(Ini& ini, IniSection& section)
{
}

void EntityTypeInfo::ReadCustom()
{

}

