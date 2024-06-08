#include "core/object.h"

Object::Object()
{

}

Object::~Object()
{

}

ObjectId Object::GetId()
{
    return reinterpret_cast<ObjectId>(this);
}
