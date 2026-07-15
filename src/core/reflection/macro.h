#pragma once

// keywords process by header tool
#define META(...)
#define CLASS(...)
#define STRUCT(...)
#define PROPERTY(...)
#define ENUM(...)
#define ENUM_CLASS(...)
#define FUNCTION(...)
#define PARAM(...)

#define GENERATED_BODY(type_name) \
    friend class __Gen_Type_##type_name; \
    friend void __Gen_Type_##type_name##__Register(); \
    friend void __JsRegister_##type_name(); \
    template<typename Archive> friend void Serialize_##type_name(Archive& ar, type_name& data);


