#include "object.h"

Object::Object()
{

}

ObjectId Object::GetId()
{
    return reinterpret_cast<ObjectId>(this);
}
