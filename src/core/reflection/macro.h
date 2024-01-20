#pragma once

#include <rttr/registration_friend.h>


// keywords process by header tool
#define META(...)
#define CLASS(...)
#define STRUCT(...)
#define INTERFACE(...)
#define PROPERTY(...)
#define ENUM(...)
#define ENUM_CLASS(...)
#define FUNCTION(...)
#define PARAM(...)

#define GENERATED_BODY(type_name) \
    friend class Serializer; \
    friend class __ReflectionType##type_name; \
    RTTR_REGISTRATION_FRIEND;


