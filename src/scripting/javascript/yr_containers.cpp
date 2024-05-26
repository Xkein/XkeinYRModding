#include "scripting/javascript/yr_data_bindings.h"
#include <Binding.hpp>
#include <core/raii_invoker.h>

void __JsRegister_YrContainers()
{
    //RegisterDynamicVectorClass(AbstractClass*);
    //RegisterDynamicVectorClass(AbstractTypeClass*);
    //RegisterDynamicVectorClass(ObjectClass*);
    //RegisterDynamicVectorClass(TechnoClass*);
    //RegisterDynamicVectorClass(TechnoTypeClass*);
    //RegisterDynamicVectorClass(InfantryClass*);
    //RegisterDynamicVectorClass(AircraftClass*);
    //RegisterDynamicVectorClass(UnitClass*);
    //RegisterDynamicVectorClass(BuildingClass*);
    //RegisterDynamicVectorClass(ColorScheme*);
    RegisterIndexClass(int, int);
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_YrContainers);
struct MyStruct0
{
    constexpr MyStruct0(int val) : field0(val) {}
    MyStruct0();
    int                  field0;
    static constexpr int field1 = 1;
    static constexpr int method0()
    {
        return 2;
    }
};
constexpr int function0()
{
    return 4;
}
constexpr int a = 0;
constexpr int b = MyStruct0::field1;
constexpr int c = MyStruct0::method0();
constexpr int d = MyStruct0(3).field0;
constexpr int e = function0();