#pragma once

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

#include <rttr/registration_friend.h>

#define GENERATED_BODY(type_name) \
    friend class __GenType_##type_name; \
    RTTR_REGISTRATION_FRIEND;


