#include "core/reflection/reflection.h"
#include "editor/editor.h"
#include "runtime/platform/platform.h"
#include "yr/api/yr_entity.h"
#include <DisplayClass.h>
#include <FootClass.h>
#include <MouseClass.h>
#include <ObjectClass.h>
#include <TacticalClass.h>
#include <WWMouseClass.h>

using namespace entt::literals;

class YrObjectInspector : public YrEditorWindow
{
    virtual void OnOpen() override;
    virtual void OnClose() override;
    virtual void OnFrame() override;

public:
    YrObjectInspector();
    virtual ~YrObjectInspector();

private:
    bool isShow {false};
};

YrObjectInspector::YrObjectInspector() {}

YrObjectInspector::~YrObjectInspector() {}

void YrObjectInspector::OnOpen()
{
    isShow = true;
}

void YrObjectInspector::OnClose()
{
    isShow = false;
}

void InspectObject(entt::meta_any& inst, const char* name);

void InspectField(entt::meta_any& inst, entt::meta_data field)
{
    FieldMeta* fieldMeta = field.custom();
    if (!fieldMeta)
    {
        ImGui::LabelText("<unknown field name>", "<unknown type> 0x%08X", inst);
        return;
    }
    const char*     fieldName = fieldMeta->name;
    entt::meta_type fieldType = field.type();

    if (fieldType.is_pointer() || fieldType.is_pointer_like() || fieldType.is_array() || fieldType.is_class() || fieldType.is_enum() || fieldType.is_arithmetic() ||
        fieldType.can_convert(entt::resolve<const char*>()))
    {
        entt::meta_any data = field.get(inst);
        InspectObject(data, fieldName);
        return;
    }

    ClassMeta*  classMeta     = fieldType.custom();
    const char* fieldTypeName = classMeta ? classMeta->name : "<unknown type>";

    ImGui::LabelText(fieldName, "%s unsupported", fieldTypeName);
}

void InspectObject(entt::meta_any& inst, const char* name)
{
    entt::meta_type type      = inst.type();
    ClassMeta*      classMeta = type.custom();
    void*           ptr       = inst.data();

    const char* typeName = classMeta ? classMeta->name : "<unknown type>";

    if (type.is_class())
    {
        if (classMeta)
        {
            if (ImGui::TreeNode(typeName, "%s %s 0x%08X", name, typeName, ptr))
            {
                for (auto&& [id, base] : type.base())
                {
                    entt::meta_any baseInst = base.from_void(ptr);
                    InspectObject(baseInst, "base");
                }

                for (auto&& [id, field] : type.data())
                {
                    FieldMeta*       fieldMeta = field.custom();
                    std::string_view fieldName = fieldMeta->name;
                    // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
                    ImGui::PushID(id);

                    InspectField(inst, field);

                    ImGui::PopID();
                }

                if (type.is_sequence_container())
                {
                    auto view = inst.as_sequence_container();
                    ImGui::Text("-- sequence size: %d", view.size());
                    for (auto elem : view)
                    {
                        InspectObject(elem, "#");
                    }
                }
                ImGui::TreePop();
            }
        }
        else
        {
            ImGui::LabelText(name ? name : "<unknown type>", "<unknown type> 0x%08X", ptr);
        }
        return;
    }

    if (type.is_pointer() || type.is_pointer_like())
    {
        entt::meta_any ref = *inst;
        if (ref)
        {
            InspectObject(ref, name);
        }
        else
        {
            ImGui::LabelText(name, "nullptr");
        }
        return;
    }

    if (type.is_array())
    {
        ArrayMeta* arrayMeta = type.custom();
        auto       elemType  = entt::resolve(arrayMeta->element);
        size_t     count     = arrayMeta->count;
        ImGui::LabelText(name, "-- array size: %d", count);
        size_t elemSize = elemType.size_of();
        for (size_t idx = 0; idx < count; idx++)
        {
            void*          elemPtr  = *(void**)((size_t)ptr + elemSize * idx);
            entt::meta_any elemInst = elemType.from_void(elemPtr);
            InspectObject(elemInst, "#");
        }
        return;
    }

    if (type.is_enum())
    {
        if (type.size_of() == 4)
        {
            uint enumVal = *(uint*)ptr;
            ImGui::LabelText(name, "enum %s unsupported = %d", typeName, enumVal);
        }
        else
        {
            ImGui::LabelText(name, "enum %s unsupported", typeName);
        }
        return;
    }

    if (type.is_arithmetic())
    {
        if (type == entt::resolve<bool>())
        {
            ImGui::Checkbox(name, (bool*)ptr);
        }
        else if (type == entt::resolve<int8>())
        {
            ImGui::InputScalar(name, ImGuiDataType_S8, ptr);
        }
        else if (type == entt::resolve<uint8>())
        {
            ImGui::InputScalar(name, ImGuiDataType_U8, ptr);
        }
        else if (type == entt::resolve<int16>())
        {
            ImGui::InputScalar(name, ImGuiDataType_S16, ptr);
        }
        else if (type == entt::resolve<uint16>())
        {
            ImGui::InputScalar(name, ImGuiDataType_U16, ptr);
        }
        else if (type == entt::resolve<int32>())
        {
            ImGui::InputScalar(name, ImGuiDataType_S32, ptr);
        }
        else if (type == entt::resolve<uint32>())
        {
            ImGui::InputScalar(name, ImGuiDataType_U32, ptr);
        }
        else if (type == entt::resolve<int64>())
        {
            ImGui::InputScalar(name, ImGuiDataType_S64, ptr);
        }
        else if (type == entt::resolve<uint64>())
        {
            ImGui::InputScalar(name, ImGuiDataType_U64, ptr);
        }
        else if (type == entt::resolve<float>())
        {
            ImGui::InputScalar(name, ImGuiDataType_Float, ptr);
        }
        else if (type == entt::resolve<double>())
        {
            ImGui::InputScalar(name, ImGuiDataType_Double, ptr);
        }
        else if (type == entt::resolve<char>())
        {
            ImGui::InputScalar(name, ImGuiDataType_S8, ptr);
        }
        else if (type == entt::resolve<long>())
        {
            ImGui::InputScalar(name, ImGuiDataType_S32, ptr);
        }
        else if (type == entt::resolve<unsigned long>())
        {
            ImGui::InputScalar(name, ImGuiDataType_U32, ptr);
        }
        else
        {
            ImGui::LabelText(name, "%s unsupported arithmetic", typeName);
        }
        return;
    }

    if (type.can_convert(entt::resolve<const char*>()))
    {
        ImGui::LabelText(name, inst.cast<const char*>());
        return;
    }
}

void InspectYrObject(AbstractClass* pObject)
{
    entt::meta_type meta = GetYrClassMeta(pObject);
    entt::meta_any  inst = meta.from_void(pObject);
    InspectObject(inst, "Inspecting Object");
}

bool showAimmingCell {false};
bool showMapClass {false};
void YrObjectInspector::OnFrame()
{
    ImGui::SetNextWindowSize(ImVec2(520, 800), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Object Inspector", &isShow))
    {
        ImGui::End();
        return;
    }
    if (!isShow)
        this->Close();

    ImGui::Checkbox("Show Map Class", &showMapClass);
    if (showMapClass)
    {
        entt::meta_any inst = entt::resolve<MapClass>().from_void(MapClass::Instance);
        InspectObject(inst, "Inspecting Object");
    }

    ImGui::Checkbox("Show Aimming Cell", &showAimmingCell);
    if (showAimmingCell)
    {
        Point2D cursorPos;
        WWMouseClass::Instance->GetCoords(&cursorPos);
        CoordStruct coord = TacticalClass::Instance->ClientToCoords(cursorPos);
        // CellStruct cell;
        // TacticalClass::Instance->CoordsToCell(&cell, &coord);
        // coord = CellClass::Cell2Coord(cell);
        // int cellHeight = MapClass::Instance->GetCellFloorHeight(coord);
        // coord = CellClass::Cell2Coord(cell, cellHeight);
        if (CellClass* pCell = MapClass::Instance->GetCellAt(coord))
        {
            InspectYrObject(pCell);
        }
    }

    for (ObjectClass* pObject : ObjectClass::CurrentObjects())
    {
        InspectYrObject(pObject);
        break;
    }

    ImGui::End();
}

IMPL_EDITOR_WINDOW(YrObjectInspector, "object_inspector");
