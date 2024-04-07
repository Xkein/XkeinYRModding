#pragma once

#include "core/reflection/reflection.h"
#include <memory>

using ObjectId = unsigned int;

CLASS()
class Object : public std::enable_shared_from_this<Object>
{
    GENERATED_BODY(Object)
protected:
    Object();
    virtual ~Object() {}

public:
    ObjectId GetId();

};