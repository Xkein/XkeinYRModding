#include "editor/editor.h"
#include "core/reflection/reflection.h"
#include "yr/api/yr_entity.h"
#include <FootClass.h>
#include <ObjectClass.h>
#include "runtime/platform/platform.h"

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

YrObjectInspector::YrObjectInspector()
{

}

YrObjectInspector::~YrObjectInspector()
{

}

void YrObjectInspector::OnOpen()
{
    isShow = true;
}

void YrObjectInspector::OnClose()
{
    isShow = false;
}

void InspectType(entt::meta_type type, void* inst);

void InspectField(entt::meta_any& inst, entt::meta_data field)
{
    entt::meta_prop prop = field.prop("name"_hs);
    if (!prop)
    {
        ImGui::LabelText("<unknown type>", "0x%08X", inst);
        return;
    }
    const char*     fieldName = field.prop("name"_hs).value().cast<const char*>();
    entt::meta_type fieldType = field.type();

    entt::meta_any data = field.get(inst);
    void* ptr = data.data();

    if (fieldType.is_pointer() || fieldType.is_pointer_like())
    {
        entt::meta_any ref = *data;
        if (ref)
        {
            InspectType(ref.type(), ref.data());
        }
        return;
    }

    if (fieldType.is_class())
    {
        InspectType(fieldType, ptr);
        return;
    }

    if (fieldType.is_arithmetic())
    {
        if (fieldType == entt::resolve<int8>()) {
            ImGui::InputScalar(fieldName, ImGuiDataType_S8, ptr);
        }
        else if (fieldType == entt::resolve<uint8>()) {
            ImGui::InputScalar(fieldName, ImGuiDataType_U8, ptr);
        }
        else if (fieldType == entt::resolve<int16>()) {
            ImGui::InputScalar(fieldName, ImGuiDataType_S16, ptr);
        }
        else if (fieldType == entt::resolve<uint16>()) {
            ImGui::InputScalar(fieldName, ImGuiDataType_U16, ptr);
        }
        else if (fieldType == entt::resolve<int32>()) {
            ImGui::InputScalar(fieldName, ImGuiDataType_S32, ptr);
        }
        else if (fieldType == entt::resolve<uint32>()) {
            ImGui::InputScalar(fieldName, ImGuiDataType_U32, ptr);
        }
        else if (fieldType == entt::resolve<int64>()) {
            ImGui::InputScalar(fieldName, ImGuiDataType_S64, ptr);
        }
        else if (fieldType == entt::resolve<uint64>()) {
            ImGui::InputScalar(fieldName, ImGuiDataType_U64, ptr);
        }
        else if (fieldType == entt::resolve<float>()) {
            ImGui::InputScalar(fieldName, ImGuiDataType_Float, ptr);
        }
        else if (fieldType == entt::resolve<double>()) {
            ImGui::InputScalar(fieldName, ImGuiDataType_Double, ptr);
        }
        return;
    }

    if (fieldType.can_convert(entt::resolve<const char*>())){
        ImGui::LabelText(fieldName, data.cast<const char*>());
        return;
    }

    ImGui::LabelText(fieldName, "<unsupported type>");
}

void InspectType(entt::meta_type type, void* inst)
{
    entt::meta_prop prop = type.prop("name"_hs);
    if (!prop)
    {
        ImGui::LabelText("<unknown type>", "0x%08X", inst);
        return;
    }
    const char* typeName = prop.value().cast<const char*>();
    if (!ImGui::TreeNode(typeName, "%s 0x%08X", typeName, inst)) {
        return;
    }

    for (auto&& [id, base] : type.base())
    {
        InspectType(base, inst);
    }
    
    entt::meta_any instance = type.from_void(inst);
    for (auto&& [id, field] : type.data())
    {
        std::string_view fieldName = field.prop("name"_hs).value().cast<const char*>();
        // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
        ImGui::PushID(id);

        InspectField(instance, field);
        
        ImGui::PopID();
    }

    ImGui::TreePop();
}

void InspectObject(AbstractClass* pObject)
{
    entt::meta_type meta = GetYrClassMeta(pObject);

    InspectType(meta, pObject);
}

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

    for (ObjectClass* pObject : ObjectClass::CurrentObjects.get())
    {
        InspectObject(pObject);
        break;
    }
    
    ImGui::End();
}

IMPL_EDITOR_WINDOW(YrObjectInspector, "object_inspector");
