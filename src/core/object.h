#pragma once

#include <memory>


using ObjectId = unsigned int;

class Object : public std::enable_shared_from_this<Object>
{
protected:
    Object();
    virtual ~Object() {}

public:
    virtual ObjectId GetId();

};